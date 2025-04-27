/*********************************************************************************************************

              Projeto Acelerômetro, Giroscópio e Termometro com ESP32s e módulo MPU-6050
        Neste projeto vamos coletar os dados de um acelerômetro e exibi-los num display OLED SSD1306

*********************************************************************************************************/
#include <Wire.h>                 // Biblioteca do barramento I2C
#include <Adafruit_GFX.h>         // Biblioteca do display OLED
#include <Adafruit_SSD1306.h>     // Biblioteca do display OLED
#include <GY6050.h>               // Biblioteca do acelerômetro e giroscópio

// Configuração do display
#define SCREEN_WIDTH 128      // Largura da imagem em pixels
#define SCREEN_HEIGHT 64      // Altura da imagem em pixels
#define OLED_RESET     4      // Pino de reset do display (ou -1 se compartilhar o pino de reset do Arduino)
#define SCREEN_ADDRESS 0x3C   // Consulte o manual para Endereço; 0x3D para 128x64, 0x3C para 128x32

// Variaveis globais
float acelX, acelY, acelZ;
float giroX, giroY, giroZ;
float tempCelsius, tempFarenheit;
char string[10];

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Cria uma instância do display
GY6050 gyro(0x68);                                                        // Cria uma instância do acelerômetro

void setup() {

  Serial.begin(115200);                 // Inicializa a comunicação serial

  // Verifica se o display está endereçado corretamente
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 não alocado."));
    for(;;); // Loop infinito  
  }
  
  // Configura o display
  display.clearDisplay();               // Limpa o buffer do display
  display.setTextColor(SSD1306_WHITE);  // Define a cor do texto
  display.dim(0);                       // Define o brilho (0 = máx)
  display.setRotation(0);               // Configura a orientação 0, 1, 2 ou 3

  // Inicializa o acelerômetro
  gyro.initialisation();
}

void loop() {

  // Obtem os dados dos sensores    
  acelX = gyro.refresh('A', 'X');                 // Obtém o eixo "X" do acelerometro
  acelY = gyro.refresh('A', 'Y');                 // Obtém o eixo "Y" do acelerometro
  acelZ = gyro.refresh('A', 'Z');                 // Obtém o eixo "Z" do acelerometro
  
  tempCelsius = gyro.refresh('T', 'C');           // Obtém a temperatura em graus Celsius
  tempFarenheit = gyro.refresh('T', 'F');         // Obtém a temperatura em graus Farenheit 
  
  giroX = gyro.refresh('G', 'X');                 // Obtém o eixo "X" do giroscópio
  giroY = gyro.refresh('G', 'Y');                 // Obtém o eixo "Y" do giroscópio
  giroZ = gyro.refresh('G', 'Z');                 // Obtém o eixo "Z" do giroscópio                       
    
  // Desenha os dados do acelerômetro na tela    
  display.clearDisplay();                         // Limpa o buffer do display
  display.drawRoundRect(20,0,40,54,4, WHITE);     // Desenha um retangulo com cantos arredondados
  display.drawLine(20,16,60,16, WHITE);           // Desenha uma linha horizontal   
    
  display.setCursor(28,4);                        // Posiciona o cursor nas coordenadas
  display.println("Acel");                        // Exibe a informação entre parenteses

  display.setCursor(32,20);                       // Posiciona o cursor nas coordenadas
  dtostrf(acelX, 3, 0, string);                   // Captura o valor da variável
  display.println(string);                        // Exibe o valor da variável

  display.setCursor(32,30);          
  dtostrf(acelY, 3, 0, string);               
  display.println(string);       
  
  display.setCursor(32,40);          
  dtostrf(acelZ, 3, 0, string);               
  display.println(string);  
     
  // Desenha dados do giroscópio na tela    
  display.drawRoundRect(64,0,40,54,4, WHITE);       
  display.drawLine(64,16,104,16, WHITE);             
  
  display.setCursor(72,4);                         
  display.println("Gyro");  

  display.setCursor(76,20);          
  dtostrf(giroX, 3, 0, string);               
  display.println(string);

  display.setCursor(76,30);          
  dtostrf(giroY, 3, 0, string);               
  display.println(string);

  display.setCursor(76,40);          
  dtostrf(giroZ, 3, 0, string);               
  display.println(string);

  // Exibe a temperatura na tela
  display.setCursor(3, 56);
  display.print(F("Temperatura: "));
  display.print(tempCelsius);
  display.print(F(" C"));
  
  display.display();       // Exibe as informações no display                             
  delay(100);              // Retem as informações no display por 100 ms antes de atualizar

}
