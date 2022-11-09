#include<SoftwareSerial.h>
SoftwareSerial BTSerial(15,14); // RX,TX
//#define kornaRole 32
//#define dortluRole 31
#define kontakBilgi 34
#define gerivitesBilgi 33

int sensorPin[20]={12,11,10,9,8,7,6,3,2,5,4,22,23,24,25,26,27,28,29,30};
String koltukDurum[20]={};
String yolcuDurum;
boolean hata=0;



void sensorOkuma(){
for(int i=0;i<20;i++){
 String koltukDurumEski=koltukDurum[i];
 koltukDurum[i]=digitalRead(sensorPin[i]); 
 delay(100);
 if(koltukDurumEski!=koltukDurum[i])
 {
 String veri=String(i)+"f"+String(koltukDurum[i]);
 BTSerial.println(veri);
}
else{}

}
}
String koltukKontrol(){
  for(int i=0;i<20;i++){
    if(koltukDurum[i]=="1"){
    yolcuDurum="1";
    break;
    }
    else{
      yolcuDurum="0";
      }
  }
  return yolcuDurum;
}


void setup() {
  BTSerial.begin(9600);
  for(int i=0;i<20;i++){
  pinMode(sensorPin[i],INPUT);
  }
  pinMode(13, OUTPUT);
 // pinMode(kornaRole,OUTPUT);
 // pinMode(dortluRole,OUTPUT);
  pinMode(kontakBilgi,INPUT);
  pinMode(gerivitesBilgi,INPUT);
  //Rölelerin elektronik devresi ters mantık bağlantılı olduğundan çıkışları HIGH yaptık
 // digitalWrite(kornaRole,HIGH);
 // digitalWrite(dortluRole,HIGH);
}
/*
kontakBilgi ve gerivitesBilgi enerji varken LOW değer döndürüyor.
DİKKAT: Araçların incelenmesi gerekiyor. Kontakta anahtar varken veya yokken hangi bilgiler geliyor.
*/
void loop() {

while(digitalRead(kontakBilgi)==1 && koltukKontrol()=="1"){
    
   if(hata==0){
  BTSerial.println("404");
  delay(400);
  BTSerial.println("404");
   hata=1;
   }
 /* 
  digitalWrite(dortluRole,LOW);
  delay(1000);
  digitalWrite(kornaRole,LOW);
  delay(2000);
  digitalWrite(kornaRole,HIGH);
  */

  if(digitalRead(kontakBilgi)==0){
  //  digitalWrite(dortluRole,HIGH);
   // digitalWrite(kornaRole,HIGH);
      yolcuDurum="0";
    BTSerial.println("200");
    hata=0;
    break;
  }
  
}

sensorOkuma(); 
//digitalWrite(dortluRole,HIGH);
//digitalWrite(kornaRole,HIGH);


}
