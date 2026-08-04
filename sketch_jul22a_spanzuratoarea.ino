#include <LiquidCrystal.h>
#include <string.h>
#include <cctype>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool jucamInca=true;
bool validCuv;
String cuvant;
String indiciu;
int vieti=0;

void afiseazaStare() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Indiciu: ");
  lcd.print(indiciu);
  lcd.setCursor(0, 1);
  lcd.print("Vieti ramase: ");
  lcd.print(vieti);
} 

bool continuareStare(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mai jucam?");

  while(Serial.available()==0){} 
  String raspuns=Serial.readStringUntil('\n');
  raspuns.trim();
  raspuns.toLowerCase();

  if(raspuns=="da"){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Asteapta reset.");
    delay(3000);
    while(Serial.available()>0){
      Serial.read();
    }
    return true;
  }else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Joc terminat.");
    return false;
  }
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop(){
  if (jucamInca==false) {
    return; 
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scrie cuvantul");
  validCuv=true;
  cuvant="";

  while(Serial.available()==0){} 
  cuvant=Serial.readStringUntil('\n');
  cuvant.trim();
  cuvant.toLowerCase();

  for(size_t i=0; i<cuvant.length(); i++){
      if(cuvant[i]<'a' || cuvant[i]>'z'){
        validCuv=false;
        break;
    }
  }
  
  if(validCuv==false || cuvant.length()>7 || cuvant.length()==0){
    lcd.clear();
    if(cuvant.length()>7){
      lcd.setCursor(0, 0);
      lcd.print("Cuvant prea lung");
      delay(2000);
    }else if(validCuv==false){
      lcd.setCursor(0,0);
      lcd.print("Cuvant invalid!!");
      lcd.setCursor(0,1);
      lcd.print("Stiu doar litere");
      delay(2000);
    }
    jucamInca=continuareStare();
    return; // pt a opri loop ul
  }

  indiciu="";
  for(int i=0; i<cuvant.length(); i++){
    indiciu+='_';
  }
  vieti=(cuvant.length())/2; 

  Serial.println(cuvant);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bun.");
  lcd.setCursor(0,1);
  lcd.print("Acum poti ghici.");
  delay(3000);

  afiseazaStare();
  while (vieti>0 && indiciu!=cuvant){
    delay(500);
    bool ghicit=false;
    if(Serial.available()>0) {
      char lit=Serial.read();
      if(lit == '\n' || lit == '\r'){
        continue;
      } 
      lit=tolower(lit);
      for(int i=0; i<cuvant.length(); i++){
        if(lit==cuvant[i] && indiciu[i]=='_'){
          indiciu[i]=cuvant[i];
          ghicit=true;
        }  
      }
      if(ghicit==false)
        vieti--;
    afiseazaStare();
    }
  }
  if(indiciu==cuvant){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bravo, ai ghicit!");
    delay(2000);
  }else if(indiciu!=cuvant && vieti==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Imi pare rau,");
    lcd.setCursor(0, 1);
    lcd.print("dar n-ai ghicit.");
    delay(2000);
  }
}
