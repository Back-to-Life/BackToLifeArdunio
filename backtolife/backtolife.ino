//#include <WiFi.h>//ESP default wi-fi entegrasyon
//#include <WiFiClientSecure.h> //ESP ile default kütüphanesi



//kablosuz ağ bilgileri
//const char* ssid="wifi";
//const char* password = "";

const int moveMount =34;
bool moveMoment=false;
int moveCounter=0;
int howMuchCounter=0;


void IRAM_ATTR ISR(){
  Serial.println("move correctt!!!! !!");
  moveMoment=true;
  moveCounter=1;
  howMuchCounter +=1;
  Serial.println(howMuchCounter);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //PIR sensörün bağlı olduğu pini tanımlıyoruz
  pinMode(moveMount,INPUT_PULLUP); 
  //eğer bir pin intterrupt(kesme) olarak tanımlayalım ki herhangi bir anda kodu durdurabililelim ve çalışabilsin. Modu RISING ayarlıyoruz çünkü gelen bir vold değeri high olacaktır.
  attachInterrupt(digitalPinToInterrupt(moveMount),ISR,RISING); // sensör algıladığında tespit edilcek ve fonksiyonumuz çalışcak

  Serial.println("Hello");

  //kablosuz ağla bağlanma
  //Serial.print("Kablosuz Ağa Bağlanıyor: ");
  //Serial.print(ssid);

  //WiFi.mode(WIFI_STA);
  //WiFi.begin(ssid,password);
  //bağlanana kadar bekletiyoruz
  //while(WiFi.status()!=WL_CONNECTED){
  //  Serial.print(".");
  //  delay(500);
  //}

  //Serial.println("");
  //Serial.println("connect wifi");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if((moveMoment)&& moveCounter==1){
    Serial.println("move correct");
    moveMoment=false; //kullandığımız için tekrar resetleyelim ki tekrar kullanabilmek için
  }
}
