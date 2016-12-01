Garden Sensors
==================

O projeto Garden Sensors, é um conjunto de sensores interligados, capaz de analisar em tempo real (configurado para ler a cada 30 minutos) a temperatura e umidade relativa do ar, e também a umidade do solo, enviando os dados para nuvem (Google Cloud Platform) através de uma Plataforma IOT.
Seus dados podem ser obtidos acessando a URL de configuração registrada na Plataforma IOT, ou através do Dashboard Garden (navegando no menu lateral esquerdo em Source -> dashboardGarden), um painel demonstrativo de visualização dos dados.

## Componentes
- NodeMCU + ESP8266
- Sensor de Umidade FC-28
- Sensor de Temperatura DHT22 ([Fonte][1])


## Bibliotecas
- Importar as seguintes bibliotecas para dentro do diretório de instalação da IDE Arduino(\Arduino\libraries\)
	- \libraries\CiotAdapter
	- \libraries\DHT-sensor-library-master
	- \libraries\SimpleTimer
	- \libraries\WiFiConnector-master
	- \libraries\WiFiManager-master
	
## IDE Arduino
- Configurar IDE Arduino para suportar ESP8266, seguindo o tutorial: [Instalando pelo Gerenciador de Placas][2]
- Abrir o código fonte hybrid.ino (\hybrid\hybrid.ino) na IDE Arduino
- Selecionar a placa (Ferramentas->Placa->NodeMCU 1.0 (ESP -12E Module))
- Selecionar frequência de CPU (Ferramentas->CPU Frequency->80MHz)
- Selecionar tamanho do flash (Ferramentas->Flash Size->4M (3M SPIFFS))
- Selecionar velocidade de upload (Ferramentas->Flash Size->115200)
- Selecionar a porta (Ferramentas->Porta->COMXX)
- Com os sensores conectados no NodeMCU, e este no computador, clicar em Upload

## Configurar WiFi pelo modo SmartConfig:
- Colocar um jumper, com uma ponta no pino D1 (GPIO 5) e a outra no GND
- Abrir o console monitor serial da IDE Arduino
- Pressionar o botao reset por 3 segundos
- Trocar o jumper do pino GND para o 3,3v (nesse momento, no console Monitor serial da IDE Arduino, aparecerá o log startSmartConfig(), indicando que o nodeMCU esta no modo Smart Config)
- Instalar o aplicativo [ESP8266 SmartConfig][3] (Nat Weerawan) disponível na Play Store (Android)
- Configurar a rede para o ESP8266 pelo app, inserindo a senha para o SSID conectado (conectar o dispositivo móvel em uma rede sem proxy de autenticação)

## Esquema Eletrônico
- O esquema pode ser visualizado abrindo do arquivo fritzing_garden.fzz através do software [Fritzing][4]

[1]: https://github.com/adafruit/DHT-sensor-library
[2]: https://github.com/esp8266/Arduino#installing-with-boards-manager
[3]: https://play.google.com/store/apps/details?id=com.cmmakerclub.iot.esptouch&hl=en
[4]: http://fritzing.org/home/