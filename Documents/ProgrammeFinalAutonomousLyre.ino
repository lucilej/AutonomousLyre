#include <MIDI.h>
#include <Servo.h>
MIDI_CREATE_DEFAULT_INSTANCE();
Servo servos[16];
int tabPositions[16];
//valeurs des notes MIDI de chaque corde, allant de sol à la (de 2 gammes au dessus)
int tabNotes[]={67,69,71,72,74,76,77,79,81,83,84,86,88,89,91,93};
//angles pour chaque servomoteur
int tabAngle1[]={50,55,60,55,60,50,70,48,58,60,60,55,60,50,60,50}; //1ere position
int tabAngle2[]={77,73,85,73,80,72,100,70,88,85,80,70,85,70,80,70}; //2eme position
//lorsqu"un servomoteur va de la 1ère à la 2ème position, il joue sa corde et idem de la 2ème à 1ère position
 
void handleNoteOn(byte channel, byte note, byte velocity) {
  int index = findNoteIndex(note);
  if (index >= 0) {
    if (tabPositions[index]==tabAngle1[index]){
      tabPositions[index] = tabAngle2[index];
      servos[index].write(tabAngle2[index]);
    }else{
      tabPositions[index] = tabAngle1[index];
      servos[index].write(tabAngle1[index]);
    }
   
  }
}
int findNoteIndex(int note) {
  for (int i = 0; i < 16; i++) {
    if (note == tabNotes[i]) {
      return i;
    }
  }
  return -1;
}
//-----------
void setup() {
  for (int i = 0; i < 16; i++) {
    servos[i].attach(i+3); //les servomoteurs utilisent les broches de 3 à 18
    tabPositions[i] = tabAngle1[i]; //la position initiale de chaque servomoteur
    servos[i].write(tabAngle1[i]);
  }
  MIDI.begin();
  MIDI.setHandleNoteOn(handleNoteOn); //dit quoi faire quand un signal de "note on" est envoyé quand c'est lu dans le void loop()
  Serial.begin(57600);
 
}
void loop() {
  MIDI.read();
}
