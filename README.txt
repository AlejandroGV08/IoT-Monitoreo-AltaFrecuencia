Metodología IoT para el Monitoreo de Sistemas en la Industria 4.0

Este repositorio presenta la implementación práctica de una metodología IoT avanzada para el monitoreo y control de sistemas en la Industria 4.0, con un enfoque específico en la recolección y procesamiento de datos en escenarios de alta frecuencia [conversación anterior].

La solución implementada aquí es el resultado de una investigación que comparó diversas metodologías y demostró resultados altamente superiores en comparación con otras evaluaciones. Esta metodología logró procesar y visualizar señales senoidales de manera fiel hasta 4 Hz, un límite significativamente mayor que las alternativas estudiadas, las cuales presentaban aliasing o distorsiones a frecuencias mucho más bajas (por encima de 220 mHz / 0.22 Hz para Arduino Cloud y 200 mHz / 0.2 Hz para AWS con InfluxDB y Grafana).

El objetivo general de esta investigación, como se plantea en la tesis, fue desarrollar una metodología basada en el Internet de las Cosas para el monitoreo de dispositivos especializada en la recolección y procesamiento de datos en escenarios de alta frecuencia. Se aborda el problema de la "recolección y procesamiento de datos de diversos dispositivos para la toma de decisiones en escenarios de alta frecuencia", destacando la importancia del "muestreo de los datos a una frecuencia superior a 1 Hz" para un análisis preciso y oportuno en la Industria 4.0.

Este proyecto busca facilitar la replicación, el estudio detallado y la comprensión práctica de una arquitectura IoT robusta y eficiente, crucial para la toma de decisiones informadas y la automatización avanzada en entornos industriales complejos.

Contenido del Repositorio:

*   `Codigo_ESP32.cpp`: Código optimizado para el microcontrolador ESP32 DevKit V1. Este script permite la captura continua de valores analógicos y su transmisión eficiente a AWS IoT Core mediante MQTT, utilizando certificados de seguridad.
*   `configuracion_aws.txt`: Guía detallada para configurar la regla en AWS IoT Core que permite la inserción directa de registros de datos en Amazon Timestream, optimizando el flujo de datos sin intermediarios como funciones Lambda.
*   `configuracion_timestream.txt`: Guía para la creación de la base de datos y tabla en Amazon Timestream, un servicio optimizado para el almacenamiento de series temporales de alta frecuencia, incluyendo la configuración de retención de datos en memoria y magnético.
*   `Codigo_Graficacion.py`: Un script de Python que utiliza AWS CLI y la biblioteca boto3 para acceder a los datos almacenados en Amazon Timestream. Incluye el uso de pandas para la transformación y estructuración de los datos, y matplotlib para la graficación y visualización de señales de alta frecuencia.
*   `requerimientos.txt`: Lista de las dependencias de Python (`boto3`, `pandas`, `matplotlib`) para facilitar la configuración del entorno de ejecución del script de análisis.
*   `Proyecto.mp4`: Video de demostración del funcionamiento del sistema, mostrando la captura y visualización de señales en tiempo real.

## Visión General de la Metodología (AWS con Timestream y Python):

Esta metodología se basa en una arquitectura robusta y escalable que integra componentes clave de AWS para un monitoreo IoT de alto rendimiento:

1.  Hardware (ESP32 DevKit V1): El microcontrolador ESP32 DevKit V1 captura continuamente señales analógicas (senoidales en las pruebas) y las transmite vía MQTT.
2.  Seguridad y Conectividad (AWS IoT Core): Los datos se envían de forma segura a AWS IoT Core, que actúa como bróker MQTT y punto de entrada para los dispositivos IoT. La autenticación se realiza mediante certificados X.509.
3.  Ingesta Directa (Regla de AWS IoT Core a Timestream): Una regla configurada en AWS IoT Core dirige los mensajes MQTT directamente a una tabla en Amazon Timestream, optimizando la latencia y eliminando intermediarios como funciones Lambda.
4.  Almacenamiento Optimizado (Amazon Timestream): Los datos de series temporales se almacenan en Amazon Timestream, un servicio diseñado para ingestión de alta velocidad y consultas eficientes.
5.  Análisis y Visualización (Python con AWS CLI/boto3/pandas/matplotlib): Un script de Python accede, procesa y grafica los datos desde Timestream, ofreciendo un control total sobre el análisis y la representación visual de las señales.

## Instrucciones Paso a Paso para la Replicación:

Para replicar y ejecutar esta metodología, sigue los siguientes pasos:

1.  Configurar el Entorno de Desarrollo del ESP32:
    *   Instala Arduino IDE y el soporte para placas ESP32 DevKit V1.
    *   Abre el archivo `Codigo_ESP32.cpp`.

2.  Obtener y Configurar los Certificados de AWS IoT Core:
    *   En la consola de AWS IoT Core, registra un nuevo "Thing" (dispositivo) y genera automáticamente los certificados (CA, Client, Private Key).
    *   Copia el contenido de estos certificados y luego pégalos en las secciones correspondientes del archivo `Codigo_ESP32.cpp`.

3.  Subir el Código al ESP32:
    *   Asegúrate de configurar las credenciales WiFi y los detalles de tu tópico MQTT en el código del ESP32.
    *   Conecta el ESP32 a tu computadora y sube el código `Codigo_ESP32.cpp` usando Arduino IDE.

4.  Crear la Base de Datos y Tabla en Amazon Timestream:
    *   Sigue las instrucciones detalladas en el archivo `configuracion_timestream.txt` para crear tu base de datos y tabla en Amazon Timestream, asegurando la configuración de retención de datos.

5.  Configurar la Regla en AWS IoT Core:
    *   Sigue las instrucciones detalladas en el archivo `configuracion_aws.txt` para crear la regla que enviará los datos de tu tópico MQTT directamente a tu tabla de Timestream.

6.  Instalar las Dependencias de Python:
    *   Instala las bibliotecas necesarias para el script de análisis. Ejecuta `pip install -r requerimientos.txt` en tu terminal.

7.  Ejecutar el Script de Python para Análisis y Graficación:
    *   Asegúrate de que tu entorno AWS CLI esté configurado y autenticado en tu máquina local.
    *   Abre el archivo `Codigo_Graficacion.py`, verifica los nombres de tu base de datos y tabla, y ejecuta el script.
    *   Observa la graficación de los datos en tiempo real.

## Resultados Clave:

*   Esta metodología fue capaz de procesar y visualizar señales senoidales de manera fiel hasta 4 Hz.
*   Ofrece una alta claridad de las señales y baja presencia de ruido en comparación con otras metodologías.
*   Proporciona control total sobre el procesamiento y la representación de las señales a través del script de Python, permitiendo ajustes y análisis personalizados.
*   Supera las limitaciones de soluciones más cerradas como Arduino Cloud y la latencia introducida por intermediarios como AWS Lambda en la metodología con InfluxDB/Grafana.

## Video de Demostración:

Puedes encontrar un video que demuestra el funcionamiento del sistema en el repositorio (Proyecto.mp4).

## Limitaciones Consideradas:

Aunque la metodología es robusta, se identificaron las siguientes limitaciones:

*   Dependencia de la red WiFi: El rendimiento puede verse afectado por la latencia o pérdida de paquetes en el entorno WiFi local.
*   Representación visual vs. datos reales: Las herramientas de graficación, como Matplotlib en este caso, pueden aplicar interpolaciones automáticas que modifican la señal mostrada.

---
### Créditos:

*   Presenta: Alejandro Gaxiola Valenzuela
*   Director: Dr. Jesús Roberto Millán Almaraz
*   Universidad: Universidad Autónoma de Sinaloa, Facultad de Informática Culiacán
*   Becado por: Consejo Nacional de Humanidades, Ciencias y Tecnologías (CVU: 1300512)
