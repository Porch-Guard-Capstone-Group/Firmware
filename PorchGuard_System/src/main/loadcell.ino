#include "loadcell.h"

Q2HX711 hx711(hx711_data_pin, hx711_clock_pin); // prep hx711

float testmass = 40.0; // calibrated mass to be added in (g) i think. will need to be adjusted for prototype
long x1 = 0L;
long x0 = 0L;
float avg_size = 10.0; // amount of averages for each mass measurement

void loadcellInit() {
  //delay(1000); // allow load cell and hx711 to settle
  // tare procedure
  for (int ii=0;ii<int(avg_size);ii++){
    delay(10);
    x0+=hx711.read();
  }
  x0/=long(avg_size);
  Serial.println("Add Calibrated Mass");
  // calibration procedure (mass should be added equal to y1)
  int ii = 1;
  while(true){
    if (hx711.read()<x0+10000){
    } else {
      ii++;
      delay(2000);
      for (int jj=0;jj<int(avg_size);jj++){
        x1+=hx711.read();
      }
      x1/=long(avg_size);
      break;
    }
  }
  Serial.println("Calibration Complete");
}

float loadcellDetect() {
  // averaging reading
  long reading = 0;
  for (int jj=0;jj<int(avg_size);jj++){
    reading+=hx711.read();
  }
  reading/=long(avg_size);
  // calculating mass based on calibration and linear fit
  float ratio_1 = (float) (reading-x0);
  float ratio_2 = (float) (x1-x0);
  float ratio = ratio_1/ratio_2;
  float mass = (testmass*ratio);
  
  Serial.print("Raw: ");
  Serial.print(reading);
  Serial.print(", ");
  Serial.println(mass);
  return mass;
}
