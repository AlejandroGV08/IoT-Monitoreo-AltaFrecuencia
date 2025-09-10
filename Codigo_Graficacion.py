
import boto3
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime, timedelta, timezone

AWS_REGION = 'us-east-2' 
DATABASE_NAME = 'esp32_iot_data' 
TABLE_NAME = 'sensor_readings'  

end_time = datetime.now(timezone.utc)
start_time = end_time - timedelta(seconds=15) 
start_time_str = start_time.strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3]
end_time_str = end_time.strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3]
print(f"Buscando datos entre {start_time_str} y {end_time_str}")

QUERY = f"""
    SELECT
        time,
        measure_value::bigint as sensor_value,
        device_id
    FROM
        "{DATABASE_NAME}"."{TABLE_NAME}"
    WHERE
        measure_name = 'valor'
        AND time BETWEEN from_iso8601_timestamp('{start_time_str}') AND from_iso8601_timestamp('{end_time_str}')
    ORDER BY
        time ASC
    """
query_client = boto3.client('timestream-query', region_name=AWS_REGION)

def run_query(query_string):
    response = query_client.query(QueryString=query_string)
    return response['Rows'], response['ColumnInfo']

def procesar_filas(filas, info_columnas):
    datos = []
    for fila in filas:
        registro = {}
        for columna, valor in zip(info_columnas, fila['Data']):
            nombre_columna = columna['Name']
            if 'ScalarType' in columna['Type']:
                tipo_escalar = columna['Type']['ScalarType']
                if tipo_escalar == 'TIMESTAMP':
                    registro[nombre_columna] = pd.to_datetime(valor['ScalarValue'], utc=True)
                elif tipo_escalar == 'DOUBLE' or tipo_escalar == 'BIGINT': 
                    registro[nombre_columna] = float(valor['ScalarValue']) 
                else:
                    registro[nombre_columna] = valor['ScalarValue']
            elif columna['Type']['Type'] == 'ROW':
                registro[nombre_columna] = valor['ScalarValue']
            else:
                registro[nombre_columna] = str(valor)
        datos.append(registro)
    return pd.DataFrame(datos)

try:
    filas_respuesta, info_columnas = run_query(QUERY)

    if not filas_respuesta:
        print("No se encontraron datos para el rango de tiempo y medida especificados.")
    else:
        df = procesar_filas(filas_respuesta, info_columnas)
        df['time'] = pd.to_datetime(df['time'], utc=True)
        df = df.sort_values(by='time')

        plt.figure(figsize=(12, 6))
        plt.plot(df['time'], df['sensor_value'], marker='o', linestyle='-', markersize=4) 
        plt.xlabel('Tiempo')
        plt.ylabel('Valor')
        plt.title(f'Datos del ESP32')
        plt.grid(True)
        plt.tight_layout()
        plt.show()

except Exception as error:
    print(f"Ocurrió un error: {error}")
