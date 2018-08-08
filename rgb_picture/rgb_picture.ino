#define B_G 3
#define B_R 5
#define B_B 6

#define M_R 9
#define M_G 10
#define M_B 11

int k =0;

void setup() {
  randomSeed(analogRead(0));
  int b_r = random(255);
  randomSeed(analogRead(0)+ 33);
  int b_g = random(255);
  randomSeed(analogRead(0)+ 13);
  int b_b = random(255);
  randomSeed(analogRead(22));
  int m_r = random(255);
  randomSeed(analogRead(0)+ 3);
  int m_g = random(255);
  randomSeed(analogRead(0)+ 54);
  int m_b = random(255);


   analogWrite(B_R, b_r);
   analogWrite(B_G, b_g);
   analogWrite(B_B, b_b);
   analogWrite(M_R, m_r);
   analogWrite(M_G, m_g);
   analogWrite(M_B, m_b);
  
}

void loop() {

  randomSeed(analogRead(0) + k);
  int b_r = random(255);
  randomSeed(analogRead(0)+ 33 + k);
  int b_g = random(255);
  randomSeed(analogRead(0)+ 13 + k);
  int b_b = random(255);
  randomSeed(analogRead(22) + k);
  int m_r = random(255);
  randomSeed(analogRead(0)+ 3 + k);
  int m_g = random(255);
  randomSeed(analogRead(0)+ 54 + k);
  int m_b = random(255);


//   analogWrite(B_R, b_r);
//   analogWrite(B_G, b_g);
//   analogWrite(B_B, b_b);
//   analogWrite(M_R, m_r);
//   analogWrite(M_G, m_g);
//   analogWrite(M_B, m_b);

  for(int i = 0, j = 255; i < 255; i++){
//    analogWrite(B_R, max( i,0));
//    analogWrite(B_G, max(i,0));
//    analogWrite(B_B, max(i,0));

    analogWrite(M_R, min(i,m_r));
    analogWrite(M_G, min(i,m_g));
    analogWrite(M_B, min(i,m_b));
//     j--;
     
    
    delay(200);
  }
//******************************************** 
  for(int i = m_b; i < 255; i++){
    analogWrite(M_B,i);
    delay(200);
  }
  int i = 0, j = 255;
  for(; i < 255; i++){
    analogWrite(B_R, min( i,255));
    analogWrite(B_G, min(i,b_g));
    analogWrite(B_B, min(i,b_b));

    analogWrite(M_R, max(m_r - j,0));
    analogWrite(M_G, max(m_g - j,0));
    analogWrite(M_B, max(255 - j,0));
     j--;
     
    
    delay(200);
  }
  for(i = 0; i > 255; i++){
    analogWrite(B_R, max(255 - i,0));
    analogWrite(B_G, max(b_g - i,0));
    analogWrite(B_B, max(b_b - i,0));

    analogWrite(M_R, min( j,m_r));
    analogWrite(M_G, min( j,m_g));
    analogWrite(M_B, min( j,255));
    j++;
    delay(200);
  }
//------------------------------------------------
  for(int i = m_r; i < 255; i++){
    analogWrite(M_R,i);
    delay(200);
  }
  for(; i < 255; i++){
    analogWrite(B_R, min( i,b_r));
    analogWrite(B_G, min(i,255));
    analogWrite(B_B, min(i,b_b));

    analogWrite(M_R, max(255 - j,0));
    analogWrite(M_G, max(m_g - j,0));
    analogWrite(M_B, max(m_b - j,0));
     j--;
     
    
    delay(200);
  }
  for(i = 0; i > 255; i++){
    analogWrite(B_R, max(b_r - i,0));
    analogWrite(B_G, max(255 - i,0));
    analogWrite(B_B, max(b_b - i,0));

    analogWrite(M_R, min( j,255));
    analogWrite(M_G, min( j,m_g));
    analogWrite(M_B, min( j,m_b));
    j++;
    delay(200);
  }
//------------------------------------------------
  for(int i = m_g; i < 255; i++){
    analogWrite(M_G,i);
    delay(200);
  }
  for(; i < 255; i++){
    analogWrite(B_R, min( i,b_r));
    analogWrite(B_G, min(i,b_g));
    analogWrite(B_B, min(i,255));

    analogWrite(M_R, max(m_r - j,0));
    analogWrite(M_G, max(255 - j,0));
    analogWrite(M_B, max(m_b - j,0));
     j--;
     
    
    delay(200);
  }
  for(i = 0; i > 255; i++){
    analogWrite(B_R, max(b_r - i,0));
    analogWrite(B_G, max(b_g - i,0));
    analogWrite(B_B, max(255 - i,0));

    analogWrite(M_R, min( j,m_r));
    analogWrite(M_G, min( j,255));
    analogWrite(M_B, min( j,m_b));
    j++;
    delay(200);
  }

  k++;
  if (k = 100) k = 0;
}   
