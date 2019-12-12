#include <Ultrasonic.h>     // obvio

//Define os pinos para o trigger e echo
#define pino_trigger 12
#define pino_echo 13

//Inicializa o sensor ultrassom
Ultrasonic ultrassom(pino_trigger, pino_echo);

//Definicoes pinos Arduino ligados a entrada da Ponte H
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int velocidade1 = 120;
int velocidade2 = 100;
long distancia, distanciaE,distanciaD; 
  
void setup(){
  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  analogWrite(9,velocidade1); // pino de velocidade
  analogWrite(10,velocidade2); // pino de velocidadez
  Serial.begin(9600);
 parar();
}

void loop(){
 //Le as informacoes do sensor, em cm 
  distancia = ultra();
  //Exibe informacoes no serial monitor
  if(distancia > 20){
    andar();
    Serial.println("andar");
  }else{
    esquerda();
    delay(350);
    distanciaE = ultra();
    delay(350);
    direita();
    delay(350);    
    distanciaD = ultra();
    delay(350);
    if(distanciaE > distanciaD){
      esquerda();
      esquerda();
      }
  }
  parar();
  distancia=0;
  delay(2000);
 }

long ultra(){
  long resp = ultrassom.read(CM); 
  return(resp);
  }


void andar(){
    //  Motor esquerdo, sentido horario - frente
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //  Motor direito, sentido horario - frente
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(300);
    parar(); // redundancia
}

void direita(){
  // Motor B no sentido horario
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4, LOW);
 // Motor esquerdo no sentido anti horario
  digitalWrite(IN1, LOW);
  digitalWrite(IN2,HIGH);
  delay(400);
  parar();
}

void esquerda(){
  // Motor direito no sentido horario
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2, LOW);
 // Motor esquerdo no sentido anti horario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH);
  delay(200);
  parar();
}

void parar(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);        
} 
