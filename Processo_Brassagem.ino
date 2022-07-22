#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x27,16,2);

#include <SoftwareSerial.h>//INCLUSÃO DE BIBLIOTECA
#include <OneWire.h>  //INCLUSÃO DE BIBLIOTECA
#include <DallasTemperature.h>//INCLUSÃO DE BIBLIOTECA

const int pinoRX = 2; //PINO DIGITAL 2 (RX)
const int pinoTX = 3; //PINO DIGITAL 3 (TX)
SoftwareSerial bluetooth(pinoRX, pinoTX); //PINOS QUE EMULAM A SERIAL, ONDE
//O PINO 2 É O RX E O PINO 3 É O TX
char dadoBluetooth = 0; // variavel que amarzena dados do bluetooth
#define led 7 // definindo o pino 7 como led 
#define dados 13// definindo o pino 13 como dados
OneWire oneWire(dados);  /* Protocolo OneWire */
/********************************************************************/
DallasTemperature sensors(&oneWire); /* encaminha referências OneWire para o sensor */
/********************************************************************/ 
/*****variveis*******/
int conta;
int escolha = 0;
int sensor = 0;

int sim = 0;
int nao = 0;

int ssim;
int nnao;

unsigned long time;
int realtemp;
int minu;
int seg;
/*************/
void setup() {
  Serial.begin(9600);// iniciando a serial 
  bluetooth.begin(9600);// inicia biblioteca 
  lcd.init();//inicia biblioteca 
  sensors.begin(); // inicia biblioteca 
  lcd.backlight();//inicia biblioteca 

  pinMode(led,OUTPUT);// definindo pino led como saida 
  lcd.setCursor(2,1);// iniciando curso na posição 
  lcd.print("escolha sua"); //escreve no LCD
  lcd.setCursor(0,2);// iniciando curso na posição 
  lcd.print("receita pelo app");//escreve no LCD
  delay(5000);
  lcd.clear(); //limpa o LCD
}
void loop(){
 
if(bluetooth.available()){ //SE O BLUETOOTH ESTIVER HABILITADO, FAZ
       dadoBluetooth = bluetooth.read(); //VARIÁVEL RECEBE O VALOR ENVIADO PELO BLUETOOTH
/*********************/  
  if(dadoBluetooth == 'A'){// se oque for recebido for igual a A 
   conta = 1; 
  }
  /*******/
  if(dadoBluetooth == 'B'){
   conta = 2; 
  }
   /*******************/
   if(dadoBluetooth == 'S'){
   sim = 1;
   nao = 0; 
  }
  if(dadoBluetooth == 'N'){
   nao = 1;
   sim = 0; 
  }
    switch(conta){
case 1:
      receita1();
      //Executa a função um
      break;
/*case 2:
      receita2();//Executa a função um
      break;*/
  }
 }
}
void leituraT(){
sensors.requestTemperatures(); /* Envia o comando para leitura da temperatura */
Serial.print(sensors.getTempCByIndex(0));
}
void receita1(){// subrotida da receita 1
  if(escolha == 0){
    lcd.setCursor(3,0);
    lcd.print("Receita 1");
    lcd.setCursor(2,1);
    lcd.print("Selecionada");
    delay(3000);


    lcd.setCursor(1,0);
    lcd.print("AMERICAN BROWN");
    lcd.setCursor(1,1);
    lcd.print("      ALE        ");
    delay(3000);


    lcd.setCursor(0,0);
    lcd.print(" Adicione Agua ");
    lcd.setCursor(4,1);
    lcd.print("tratada");
    delay(5000);

    lcd.clear();
       /******/
    escolha = 1;
  }
/************decisão 1 *******/
  if(escolha == 1){
    lcd.setCursor(0,0);
    lcd.print("Agua adicionada?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 1){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Iniciando etapa");
      lcd.setCursor(3,1);
      lcd.print("De Mostura  ");
      delay(3000);
       escolha = 20;
      lcd.clear();
        
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 1;
  }
/************decisão 2*******/
  if(escolha == 20){
    ssim = 0;
    sim = 0;
    lcd.setCursor(1,0);
    lcd.print("Adicione todos  ");
    lcd.setCursor(5,1);
    lcd.print("maltes");
    delay(3000);
    lcd.clear();
    escolha = 2;
    
}
 if(escolha == 2){
    lcd.setCursor(0,0);
    lcd.print("Maltes inseridos?");
    lcd.setCursor(0,1);
    lcd.print("sim      ");
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 2){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
        
      lcd.setCursor(0,0);
      lcd.print("Inicio das etapas");
      lcd.setCursor(1,1);
      lcd.print("   De Mistura");
      delay(3000);
       escolha = 3;
      lcd.clear();
       
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 2;
  }
/********inicio das etapas de mostura********/
while(escolha == 3){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 52){
       
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 15){    //AJUSTE DE TEMPO 
     escolha = 4; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Primeira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/****************************/
while(escolha == 4){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
leituraT();
     if(sensors.getTempCByIndex(0) >= 67){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 60){    //AJUSTE DE TEMPO 
     escolha = 5; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Segunda Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/**********************************/
while(escolha == 5){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 10){    //AJUSTE DE TEMPO 
     escolha = 6; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Terceira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
   }
  
/************fim das 3 atepas de mustura*******/
if(escolha == 6){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Iniciando Etapa  ");
      lcd.setCursor(0,1);
      lcd.print(" De Fervura  ");
      
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("UM");
      delay(3000);
       escolha = 7;
      lcd.clear();
}
/********inicio das etapas de fervura********/
while(escolha == 7){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 30){    //AJUSTE DE TEMPO 
     escolha = 21; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Primeira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/****************************/
if(escolha == 21){
    lcd.setCursor(0,0);
      lcd.print("Insira o Simcoe");
    lcd.setCursor(6,1);
    lcd.print("6g"         );
    delay(3000);
     lcd.clear();
   escolha = 8;
}
if(escolha == 8){
    lcd.setCursor(0,0);
    lcd.print("Simcoe inserido?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 8){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("Dois");
      delay(3000);
       escolha = 9;
      lcd.clear();
        /*****/
  }
      if(nao == 1 && escolha == 8){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 8;
  }
/*******************************/
while(escolha == 9){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 40){    //AJUSTE DE TEMPO 
     escolha = 22; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("segunda Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
       minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/****************************/
if(escolha == 22){
  ssim = 0;
   sim = 0;
    lcd.setCursor(0,0);
    lcd.print("Insira o Simcoe");
    lcd.setCursor(6,1);
    lcd.print("20g"         );
    delay(3000);
     lcd.clear();
   escolha = 10;
}
if(escolha == 10){
    lcd.setCursor(0,0);
    lcd.print("Simcoe inserido?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 10){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("três");
      delay(3000);
       escolha = 11;
      lcd.clear();
        /*****/
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 8;
  }
/*******************************/
while(escolha == 11){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      //lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 20){    //AJUSTE DE TEMPO 
     escolha = 12; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("terceira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
       minu = 0;
     delay(3000);
     lcd.clear();
     }
 }
    
    
    if(escolha == 12){
    lcd.setCursor(0,0);
    lcd.print("Escolhar sua");
    lcd.setCursor(0,1);
    lcd.print("Proxima receita");
    delay(2000);
    lcd.setCursor(1,0);
    lcd.print("Voltando para");
    lcd.setCursor(5,1);
    lcd.print("O menu");
    delay(2000);
      conta = 0;
      escolha = 0;
      lcd.clear();
  }
}

void receita2(){// subrotida da receita 1
  if(escolha == 0){
    lcd.setCursor(3,0);
    lcd.print("Receita 2");
    lcd.setCursor(2,1);
    lcd.print("Selecionada");
    delay(3000);


    lcd.setCursor(1,0);
    lcd.print("TRAPPIST STYLE");
    lcd.setCursor(1,1);
    lcd.print("   SINGLE     ");
    delay(3000);


    lcd.setCursor(0,0);
    lcd.print(" Adicione Agua ");
    lcd.setCursor(4,1);
    lcd.print("tratada");
    delay(5000);

    lcd.clear();
       /******/
    escolha = 1;
  }
/************decisão 1 *******/
  if(escolha == 1){
    lcd.setCursor(0,0);
    lcd.print("Agua adicionada?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 1){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Iniciando etapa");
      lcd.setCursor(3,1);
      lcd.print("De Mostura  ");
      delay(3000);
       escolha = 20;
      lcd.clear();
        
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 1;
  }
/************decisão 2*******/
  if(escolha == 20){
    ssim = 0;
    sim = 0;
    lcd.setCursor(1,0);
    lcd.print("Adicione todos  ");
    lcd.setCursor(5,1);
    lcd.print("maltes");
    delay(3000);
    lcd.clear();
    escolha = 2;
    
}
 if(escolha == 2){
    lcd.setCursor(0,0);
    lcd.print("Maltes inseridos?");
    lcd.setCursor(0,1);
    lcd.print("sim      ");
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 2){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
        
      lcd.setCursor(0,0);
      lcd.print("Inicio das etapas");
      lcd.setCursor(1,1);
      lcd.print("   De Mistura");
      delay(3000);
       escolha = 3;
      lcd.clear();
       
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 2;
  }
/********inicio das etapas de mostura********/
while(escolha == 3){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
      if(sensors.getTempCByIndex(0) >= 45){
     
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 5){    //AJUSTE DE TEMPO 
     escolha = 4; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Primeira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/****************************/
while(escolha == 4){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
leituraT();
     if(sensors.getTempCByIndex(0) >= 52){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 10){    //AJUSTE DE TEMPO 
     escolha = 5; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Segunda Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/**********************************/
while(escolha == 5){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
leituraT();
     if(sensors.getTempCByIndex(0) >= 64){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 60){    //AJUSTE DE TEMPO 
     escolha = 55; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Terceira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
   }
/********************************/
while(escolha == 55){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 10){    //AJUSTE DE TEMPO 
     escolha = 6; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Quarta Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
   }
  
/************fim das 3 atepas de mustura*******/
if(escolha == 6){
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Iniciando Etapa  ");
      lcd.setCursor(0,1);
      lcd.print(" De Fervura  ");
      
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("UM");
      delay(3000);
       escolha = 7;
      lcd.clear();
}
/********inicio das etapas de fervura********/
while(escolha == 7){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) == 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 30){    //AJUSTE DE TEMPO 
     escolha = 21; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("Primeira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
      minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/************60min****************/
if(escolha == 21){
    lcd.setCursor(0,0);
    lcd.print("Insira o Hallertau");
    lcd.setCursor(5,1);
    lcd.print("25g"         );
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Insira o  Saaz");
    lcd.setCursor(5,1);
    lcd.print("20g"         );
    delay(3000);
     lcd.clear();
   escolha = 8;
}
if(escolha == 8){
    lcd.setCursor(0,0);
    lcd.print("Produtos inserido?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 8){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("Dois");
      delay(3000);
       escolha = 9;
      lcd.clear();
        /*****/
  }
      if(nao == 1 && escolha == 8){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 8;
  }
/*******************************/
while(escolha == 9){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 30){    //AJUSTE DE TEMPO 
     escolha = 22; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("segunda Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
       minu = 0;
     delay(3000);
     lcd.clear();
     }
}
/************30****************/
if(escolha == 22){
  ssim = 0;
   sim = 0;
    lcd.setCursor(0,0);
    lcd.print("Insira o Hallertau");
    lcd.setCursor(5,1);
    lcd.print("10g"         );
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Insira o  Saaz");
    lcd.setCursor(5,1);
    lcd.print("10g"         );
    delay(3000);
     lcd.clear();
   escolha = 10;
}
if(escolha == 10){
    lcd.setCursor(0,0);
    lcd.print("Produtos inserido?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 10){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("três");
      delay(3000);
       escolha = 11;
      lcd.clear();
        /*****/
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 8;
  }
/*******************************/
while(escolha == 11){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      lcd.setCursor(13,1);
     lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 25){    //AJUSTE DE TEMPO 
     escolha = 23; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("terceira Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
       minu = 0;
     delay(3000);
     lcd.clear();
     }
 }
/************5min******************/
if(escolha == 23){
  ssim = 0;
   sim = 0;
    lcd.setCursor(0,0);
    lcd.print("Insira o Hallertau");
    lcd.setCursor(5,1);
    lcd.print("25g"         );
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Insira o  Saaz");
    lcd.setCursor(5,1);
    lcd.print("20g"         );
    delay(3000);
     lcd.clear();
   escolha = 10;
}
if(escolha == 10){
    lcd.setCursor(0,0);
    lcd.print("Produtos inserido?");
    lcd.setCursor(0,1);
    lcd.print("sim"           );
    lcd.setCursor(13,1);
    lcd.print("nao");
  }
    if(sim == 1 && escolha == 10){
      ssim = 2;    
    }
      if(ssim == 2){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Inicio da Etapa");
      lcd.setCursor(4,1);
      lcd.print("três");
      delay(3000);
       escolha = 12;
      lcd.clear();
        /*****/
  }
      if(nao == 1 && escolha == 1){
      nnao = 1;      
    }
      if(nnao == 1){
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Realize A Pre   ");
      lcd.setCursor(0,1);
      lcd.print("Etapa Essenciai"); 
      delay(3000);
      lcd.clear();
         /*****/
      nnao = 0;
      nao = 0; 
      escolha = 8;
  }
/***********************************/
while(escolha == 12){ //CTRAL+C / MUDAR ESCOLHA PARA VALOR DA OPÇAO A CIMA NO SIM 
   ssim = 0;
   sim = 0;
  leituraT();
     if(sensors.getTempCByIndex(0) >= 76){
      relogio();
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
      lcd.print("Temperatura");
      lcd.setCursor(11,0);
      lcd.print(minu);
      lcd.setCursor(3,0);
      lcd.print("Minutos:");       
      digitalWrite(led, 0);
   }
   else
   {
      
      digitalWrite(led, 1);
      lcd.setCursor(3,0);
      lcd.print("AJUSTANDO");
      lcd.setCursor(0,1);
      lcd.print("TEMPERATURA");
      lcd.setCursor(13,1);
      lcd.print(sensors.getTempCByIndex(0));
      lcd.setCursor(0,1);
   }
   if(minu == 5){    //AJUSTE DE TEMPO 
     escolha = 13; // MUDAR ESCOLHA PARA O PROXIMO NUMERO
        /****/  
     lcd.setCursor(0,0);
     lcd.print("quarta Etapa  "); //MUDAR SEQUENCIA
     lcd.setCursor(0,1);
     lcd.print("    Concluida       ");
      relogio();
       minu = 0;
     delay(3000);
     lcd.clear();
     }
 }
    
/********************************************/    
    if(escolha == 13){
    lcd.setCursor(0,0);
    lcd.print("Escolhar sua");
    lcd.setCursor(0,1);
    lcd.print("Proxima receita");
    delay(2000);
    lcd.setCursor(1,0);
    lcd.print("Voltando para");
    lcd.setCursor(5,1);
    lcd.print("O menu");
    delay(2000);
      conta = 0;
      escolha = 0;
      lcd.clear();
  }
}

void relogio(){
  
  int time = millis();
  int realtemp = time / 1000;
  seg++;
  Serial.println(seg);


int tempo = millis();
int ult_tempo;
if(tempo - ult_tempo >= 1000)

/*****************/
if(seg >= 60) {
seg = 0;
minu++;
}
/**************/
if(minu == 60) {
minu = 0;
realtemp++;
 }
}