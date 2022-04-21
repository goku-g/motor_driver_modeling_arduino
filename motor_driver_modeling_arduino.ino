// code for measuring voltage by using voltage sensor and arduino.
//goku-g
float r1 = 30000.0;
float r2 = 7500.0;

float voltage_out = 0.0;
float voltage_in = 0.0;
int in_value = 0;
int out_value = 0;
int temp = 5;

const int in_pin = A2;
const int out_pin = A1;

const int ln_1 = 5;
const int ln_2 = 4;
const int en = 6;

double in_time = 0.00;
double out_time = 0.00;

void setup()
{
  pinMode(en, OUTPUT);
  pinMode(ln_1, OUTPUT);
  pinMode(ln_2, OUTPUT);

  digitalWrite(ln_1,HIGH);
  digitalWrite(ln_2,LOW);
  Serial.begin(9600);
}

float get_voltage(int value)
{
  float v_out = (value * 5.0) / 1024.0;
  float v_in = v_out / (r2/(r1+r2));
  return v_in;
}

void loop()
{
  Serial.println("********************************************************");
  
  in_value = analogRead(in_pin);
  Serial.print("Input = ");
  voltage_in = get_voltage(in_value);
  Serial.println(voltage_in);
  
  Serial.println("PWM Signal!!!!");
  analogWrite(en,255);
  in_time = micros();
  
  out_value = analogRead(out_pin);
  while(out_value < temp)
  {
    temp = out_value;
    out_value = analogRead(out_pin);
  }
//  Serial.print("Out value = ");
//  Serial.println(out_value);
  
  out_time = micros();

  Serial.print("Output = ");
  voltage_out = get_voltage(out_value);
  Serial.println(voltage_out);
  
  double delay_time = out_time - in_time;
  Serial.print("Time delay: ");
  Serial.println(delay_time);
  
  out_value = 0;
  temp = 5;
  analogWrite(en,0);
  delay(300);
}
