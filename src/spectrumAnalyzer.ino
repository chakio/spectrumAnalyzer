#include <Adafruit_NeoPixel.h>
#define msg7RESET 4
#define msg7Strobe 3
#define msg7DCout 5
#define Switch 6
#define SLED 5
#define Volume 4
#define Relay 2
#define LEDPIN 8
#define NUMPIXELS    56

int spectrumRead[7]; 
int spectrumVolume[7];
int colorvalue[7];
int allvol;
int peak[7];
int peakvol[7];
int CLstep,CLstep2;
int CLtime,CLStime,CLspeed,CLvol;
bool CLfirst=false;
bool CLfirst2=false;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int delayval = 1; // delay for half a second
int pixel[7][8];
unsigned long SWStime,SWtime;
int maxF,maxV;
int bassmax;
int mode=0;
bool modenext=false;
void modes(int modenum);
void getspectrum();
void modechange();

void setup() {
  for(int i=0;i<7;i++)
  {
    for(int j=0;j<8;j++)
    {
      pixel[i][j]=8*i+(7-j);
    }
  }
  pinMode(msg7RESET, OUTPUT);
  pinMode(msg7Strobe, OUTPUT);
  pinMode(Relay, OUTPUT);
  pinMode(Switch,INPUT);
  pinMode(SLED, OUTPUT);
  //digitalWrite(Switch,LOW);
  pixels.begin();
  Serial.begin(9600);
  CLspeed=(int)map(analogRead(Volume),0,1024,20,200);
}

void setpixel(int num,double colornum,double brightness)
{
  int red,green,blue;
  if(colornum<100)
  {
    red=(double)255/50*colornum-255;
  }
  else
  {
    red=(double)-255/50*colornum+765;
  }
  if(red<0)
  {
    red=0;
  }

  if(colornum<50)
  {
    green=(double)255/50*colornum;
  }
  else
  {
    green=(double)-255/50*colornum+510;
  }
  if(green<0)
  {
    green=0;
  }
  if(colornum<100)
  {
    blue=(double)-255/50*colornum+255;
  }
  else
  {
    blue=(double)255/50*colornum-510;
  }
  if(blue<0)
  {
    blue=0;
  }
  red=(double)red/255*brightness;
  green=(double)green/255*brightness;
  blue=(double)blue/255*brightness;

  if(colornum==200)
  {
    red=(double)250/255*brightness;
    green=(double)250/255*brightness;
    blue=(double)250/255*brightness;
  }
   pixels.setPixelColor(num, pixels.Color(red,green,blue));
   
}
void loop() 
{
  modechange();
  getspectrum();
  modes(mode);
  pixels.show();  
  //Serial.println(maxF);
}
void getspectrum()
{
  digitalWrite(msg7RESET, HIGH);          // reset the MSGEQ7's counter
  delay(3);
  digitalWrite(msg7RESET, LOW);
    
   for (int x = 0; x < 7; x++)
   {
      digitalWrite(msg7Strobe, LOW);      // output each DC value for each freq band
      delayMicroseconds(35); // to allow the output to settle
      spectrumRead[x] = analogRead(msg7DCout);  
      colorvalue[x] = map(spectrumRead[x], 0, 1024, 0, 125);  // scale analogRead's value to Write's 255 max
      digitalWrite(msg7Strobe, HIGH);
   }
   maxV=0;
   for(int i=0;i<7;i++)
   {
      maxV=max(maxV,spectrumRead[i]);
      if(maxV==spectrumRead[i])
      {
        maxF=i;
      }
      if(spectrumRead[i]>peak[i])
      {
        peak[i]=spectrumRead[i];
      }
   }
   allvol=0;
   for(int i=0;i<7;i++)
   {
     spectrumVolume[i]=(spectrumRead[i]+50)/128;
     allvol+=spectrumRead[i];
   }
   allvol=(double)allvol/7/1024*200;
}
void modechange()
{
  if(digitalRead(Switch)==HIGH)
  {
    SWStime=millis();
    digitalWrite(SLED,LOW);
    modenext=false;
  }
  else
  {
    digitalWrite(SLED,HIGH);
    SWtime=millis()-SWStime;
    if(SWtime%500<200)
    {
      if(modenext==false)
      {
        modenext=true;
        if(modenext)
        {
          mode++;
          if(mode==8)
          {
            mode=0;
          }
        }
      }
    }
    else
    {
      modenext=false;
    }
  }
}

void modes(int modenum)
{
  switch (modenum)
  {
    
  
    case 0://各スペクトルの音量毎に色を変える
    {
      for(int i=0;i<7;i++)
      { 
        for(int j=0;j<spectrumVolume[i];j++)
        {
          setpixel(pixel[i][j],colorvalue[i],map(analogRead(Volume),0,1024,0,255) );
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      break;
    }
   
    
    case 1://周波数によって色が変わる
    {
      for(int i=0;i<7;i++)
      {
        for(int j=0;j<spectrumVolume[i];j++)
        {
          setpixel(pixel[i][j],(double)100/6*i,map(analogRead(Volume),0,1024,0,255) );
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      break;
    }

    
    case 2://ピークホールド
    {
      for(int i=0;i<7;i++)
      { 
        colorvalue[i]=(double)colorvalue[i]*8/7;
        if(colorvalue[i]>100)
        {
          colorvalue[i]=100;
        }
        peakvol[i]=peak[i]/128;
        for(int j=0;j<spectrumVolume[i];j++)
        {
          setpixel(pixel[i][j],colorvalue[i],map(analogRead(Volume),0,1024,0,255) );
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
        setpixel(pixel[i][peakvol[i]], 200,map(analogRead(Volume),0,1024,0,255));
        peak[i]-=15;
      }
      break; 
    }

    

    case 3://全音量で明るさを変える
    {
      if(allvol<50)
      {
        allvol=0;
      }
      /*else
      {
        allvol=250;
      }*/
      for(int i=0;i<7;i++)
      {
        for(int j=0;j<8;j++)
        {
          setpixel(pixel[i][j],(double)100/6*maxF,allvol );
        }
      }
      break;
    }

    

    case 4://カラースワイプ
    {
  
      CLStime=millis()/CLspeed;
      CLstep=CLStime%7;
      if(CLstep==0)
      {
        CLspeed=(int)map(analogRead(Volume),0,1024,20,200);
        if(CLfirst)
        {
          CLstep2+=1;
          if(CLstep2>11)
          {
            CLstep2=0;
          }
          CLfirst=false;
        }
      }
      else
      {
        CLfirst=true;
      }
      for(int i=0;i<7;i++)
      {  
        if(i<=CLstep)
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            setpixel(pixel[i][j],(double)150/12*(CLstep2),250/(CLstep+1-i)/(CLstep+1-i) );
          }
        }
        else
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            if(CLstep2==0)
            {
              setpixel(pixel[i][j],(double)150/12*(11),250/(CLstep+7-i)/(CLstep+7-i) );
            }
            else
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2-1),250/(CLstep+7-i)/(CLstep+7-i) );
            }
          }
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      break;
    }


    
    case 5://カラースワイプクロス
    {
      CLStime=millis()/CLspeed;
      CLstep=CLStime%7;
      if(CLstep==0)
      {
        CLspeed=(int)map(analogRead(Volume),0,1024,5,100);
        if(CLfirst)
        {
          CLstep2+=1;
          if(CLstep2>11)
          {
           CLstep2=0;
          }
          CLfirst=false;
        }
      }
      else
      {
        CLfirst=true;
      }
      for(int i=0;i<7;i++)
      { 
        if(i==CLstep)
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            setpixel(pixel[i][j],(double)150/12*(CLstep2),250/(CLstep+1-i)/(CLstep+1-i) );
          }
        }
        else if(i==6-CLstep)
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            if(CLstep2>5)
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2-6),250/(6-CLstep+1-i)/(6-CLstep+1-i) );
            }
            else
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2+6),250/(6-CLstep+1-i)/(6-CLstep+1-i) );
            }
          }
        }
        else
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            if(CLstep2==0)
            {
              setpixel(pixel[i][j],(double)150/12*(11),250/(CLstep+7-i)/(CLstep+7-i)*0 );
            }
            else
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2-1),250/(CLstep+7-i)/(CLstep+7-i)*0  );
            }
          }
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      break;
    }

    
    case 6://周波数によって色が変わる(フェードインアウト)
    {
      CLStime=millis()/CLspeed;
      CLstep=CLStime%10;
      CLspeed=(int)map(analogRead(Volume),0,1024,5,200);
      if(CLfirst)
      {
        if(CLstep!=CLstep2)
        {
          if(CLstep==0)
          {
            CLfirst=false;
            CLvol=255*(11-CLstep)/10;
          }
          else
          {
            CLvol=255*(CLstep+1)/10;
          }
        }
        else
        {
          CLvol=255*(CLstep+1)/10;
        }
      }
      else
      {
        if(CLstep!=CLstep2)
        {
          if(CLstep==0)
          {
            CLfirst=true;
            CLvol=255*(CLstep+1)/10;
          }
          else
          {
            CLvol=255*(11-CLstep)/10;
          }
        }
        else
        {
          CLvol=255*(11-CLstep)/10;
        }
      }
      
      for(int i=0;i<7;i++)
      {
        for(int j=0;j<spectrumVolume[i];j++)
        {
          setpixel(pixel[i][j],(double)100/6*i,CLvol );
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      CLstep2=CLstep;
      break;
    }  

    case 7://カラースワイプone point
    {
  
      CLStime=millis()/CLspeed;
      CLstep=CLStime%7;
      if(CLstep==0)
      {
        CLspeed=(int)map(analogRead(Volume),0,1024,20,200);
        if(CLfirst)
        {
          CLstep2+=1;
          if(CLstep2>11)
          {
            CLstep2=0;
          }
          CLfirst=false;
        }
      }
      else
      {
        CLfirst=true;
      }
      for(int i=0;i<7;i++)
      {  
        if(i<=CLstep)
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            if(j==spectrumVolume[i]-1)
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2),250/(CLstep+1-i)/(CLstep+1-i)/(CLstep+1-i) );
            }
            else
            {
              setpixel(pixel[i][j],(double)150/12*(CLstep2),0 );
            }
          }
        }
        else
        {
          for(int j=0;j<spectrumVolume[i];j++)
          {
            if(CLstep2==0)
            {
              if(j==spectrumVolume[i]-1)
              {
                setpixel(pixel[i][j],(double)150/12*(11),250/(CLstep+7-i)/(CLstep+7-i) /(CLstep+7-i));
              }
              else
              {
                setpixel(pixel[i][j],(double)150/12*(CLstep2),0 );
              }
            }
            else
            {
              if(j==spectrumVolume[i]-1)
              {
                setpixel(pixel[i][j],(double)150/12*(CLstep2-1),250/(CLstep+7-i)/(CLstep+7-i)/(CLstep+7-i) );
              }
              else
              {
                setpixel(pixel[i][j],(double)150/12*(CLstep2),0 );
              }
            }
          }
        }
        for(int j=spectrumVolume[i];j<8;j++)
        {
          pixels.setPixelColor(pixel[i][j], pixels.Color(0,0,0));
        }
      }
      break;
    }
    case 8://各スペクトルの音量毎に色を変える
    {
      int bassvolume=0,treblevolume=0;
      for(int i=0;i<4;i++)
      {
        bassvolume+=spectrumRead[i];
        treblevolume+=spectrumRead[i+3];
      }
      bassvolume/=(4*100);
      treblevolume/=(4*100);

      for(int j=0;j<bassvolume;j++)
      {
        setpixel(pixel[0][j],50,map(analogRead(Volume),0,1024,0,255) );
      }
      for(int j=bassvolume;j<8;j++)
      {
        setpixel(pixel[0][j],50,0 );
      }
      for(int j=0;j<treblevolume;j++)
      {
        setpixel(pixel[6][j],50,map(analogRead(Volume),0,1024,0,255) );
      }
      for(int j=treblevolume;j<8;j++)
      {
        setpixel(pixel[6][j],50,0 );
      }
     
      break;
    }
  }
}
