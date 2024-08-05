import cc.arduino.*;
import processing.serial.*;

import ddf.minim.*;
import ddf.minim.analysis.*;
PImage img;
Minim minim;
AudioPlayer song;
BeatDetect beat;
BeatListener bl;
Arduino arduino;
float kickSize, snareSize, hatSize;
int pin1=12;
int pin2=11;
int pin3=10;
class BeatListener implements AudioListener
{
  private BeatDetect beat;
  private AudioPlayer source;
  
  BeatListener(BeatDetect beat, AudioPlayer source)
  {
    this.source = source;
    this.source.addListener(this);
    this.beat = beat;
  }
  
  void samples(float[] samps)
  {
    beat.detect(source.mix);
  }
  
  void samples(float[] sampsL, float[] sampsR)
  {
    beat.detect(source.mix);
  }
}

void setup()
{
  size(512, 300);
  
    arduino = new Arduino(this, Arduino.list()[0], 57600);
    minim = new Minim(this);
  
  song = minim.loadFile("Song (2).mp3", 4096);
  song.play();
  beat = new BeatDetect(song.bufferSize(), song.sampleRate());
  beat.setSensitivity(300);  
  kickSize = snareSize = hatSize = 16;
  bl = new BeatListener(beat, song);  
  textFont(createFont("segoe print bold", 16));
  textAlign(CENTER);
  arduino.pinMode(pin1,Arduino.OUTPUT);
  arduino.pinMode(pin2,Arduino.OUTPUT);
  arduino.pinMode(pin3,Arduino.OUTPUT);
  //img=loadImage("about.png");
}

void draw()
{
  noStroke();
  background(0);
  //image(img,0,0,width,height);
  float rectW = width / beat.detectSize();
  for(int i = 0; i < beat.detectSize(); ++i)
  {
    // test one frequency band for an onset
    if ( beat.isOnset(i) )
    {
      fill(0,200,0);
      rect( i*rectW, 0, rectW, height);
    }
  }

  int lowBand = 5;
  int highBand = 15;

  int numberOfOnsetsThreshold = 4;
  if ( beat.isRange(lowBand, highBand, numberOfOnsetsThreshold) )
  {
    fill(232,179,2,200);
    rect(rectW*lowBand, 0, (highBand-lowBand)*rectW, height);
  }
  
  if ( beat.isKick() ) {
    kickSize = 32;
    arduino.digitalWrite(pin1, Arduino.HIGH);
  }
  if ( beat.isSnare() ){
  snareSize = 32;
  arduino.digitalWrite(pin2, Arduino.HIGH);
  }
  if ( beat.isHat() ){
  hatSize = 32;
  arduino.digitalWrite(pin3, Arduino.HIGH);
  }
  arduino.digitalWrite(pin1, Arduino.LOW);
  arduino.digitalWrite(pin2, Arduino.LOW);
  arduino.digitalWrite(pin3, Arduino.LOW);
  fill(0);
    
  textSize(kickSize);
  text("KICK", width/4, height/2);
  
  textSize(snareSize);
  text("SNARE", width/2, height/2);
  
  textSize(hatSize);
  text("HAT", 3*width/4, height/2);
  
  kickSize = constrain(kickSize * 0.95, 16, 32);
  snareSize = constrain(snareSize * 0.95, 16, 32);
  hatSize = constrain(hatSize * 0.95, 16, 32);
}
