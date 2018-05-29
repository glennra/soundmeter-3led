unsigned int sampleWindow = 50;

int soundInPin = A0;
int redPin = 9;
int yelPin = 8;
int grnPin = 7;

int sound = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(yelPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(soundInPin, INPUT);

  Serial.begin(9600);
  led_test();
}

void led_test() {
for(int j=0; j<10; j++)
{
  for(int i=grnPin; i<=grnPin+2; i++)
  {
    pinMode(i, OUTPUT);
    //Serial.print("pin ");
    //Serial.println(i);
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
}
}

unsigned int soundSample() {

  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    int sample = analogRead(soundInPin);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  return peakToPeak;
}

// main program - runs over and over again
void loop() {

  int soundNow = soundSample();
  if(soundNow > sound)
  {
    sound = soundNow;
  }
  if(sound > 600)
  {
    sound = 600;
  }

  //Serial.println(sound);
  for(int i=grnPin; i<=grnPin+2; i++)
  {
    digitalWrite(i, LOW);

    if(sound > 400)
    {
      digitalWrite(redPin, HIGH);
    }
    else if(sound > 200)
    {
      digitalWrite(yelPin, HIGH);
    }
    else
    {
      digitalWrite(grnPin, HIGH);
    }
  }

  sound = sound - 3;
  if(sound < 0)
  {
    sound = 0;
  }
}
