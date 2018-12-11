import ddf.minim.*;
import ddf.minim.analysis.*;
 
Minim minim;
AudioPlayer song;
FFT fft;

float rot;

float[][] terrain;
float colors[];
int cols =152;
int rows = 152;
float rotx,roty,rotz;
float zoom = 1;

void setup() {
  size(1200,1000,P3D);
  noSmooth();
  minim = new Minim(this);
   song = minim.loadFile("C:/MUSIC_VISUALIZER_FINAL/africa-toto.wav", 512);
   song.play();
   fft = new FFT(song.bufferSize(), song.sampleRate());
  terrain = new float[cols][rows];
  colors = new float[154];
  for (int n = 0; n < colors.length; n++) {
    colors[n] = random(150);
}

}


void draw() {
  PVector space = new PVector();
  PVector space1 = new PVector();
  PVector space2 = new PVector();
  PVector space3 = new PVector();
  PVector spin = new PVector(100, 100, 500);
  float theta;
  float theta1;
  
  background(0);
  noiseDetail(2,0.1);
 for (int y = 0; y < rows; y++) {
   for (int x = 0; x < cols; x++) {
      terrain[x][y] = map(song.right.get(y), 0, 2, 0, 150); 
 }
 }
  camera(width/2, height/2, (height/zoom) / tan(PI*30.0 / 180.0), width/2.0, height/2.0, 0, 0, 1, 0);
  
  
  translate(width/2, height/2, 0);
  
 if (keyPressed == true){
   if(key == 'w' || key == 'W')
   {
    rotx -= 0.01;
   } 
   if(key == 's' || key == 'S')
   {
    rotx += 0.01;
   } 
   if(key == 'a' || key == 'A')
   {
    roty -= 0.01;
   } 
   if(key == 'd' || key == 'D')
   {
    roty += 0.01;
   } 
   if(key == 'q' || key == 'Q')
   {
    rotz -= 0.01;
   } 
   if(key == 'e' || key == 'E')
   {
    rotz += 0.01;
   } 
   if(key == 'o' || key == 'O')
   {
    zoom -= 0.03;
   } 
   if(key == 'p' || key == 'P')
   {
    zoom += 0.03;
   } 
 }
 
 
  rotateX(rotx);
  rotateY(roty);
  rotateZ(rotz);

  
  for (int j = 0; j <= 150; j += 1) {
    theta = (PI/75)*j;
    theta1 = (PI/75)*(j+1);
    beginShape(QUADS);
    for (int i = 0; i <= 150; i += 1) {
      float u = map (i, 0, 150, -10, 10);
      float u1 = map (i+1, 0, 150, -10, 10);
      
      space.x = (3+ terrain[i][j]/50)*spin.x*cos(theta)*sqrt(1-(u*u)) ;
      space.y = (3+ terrain[i][j]/50)*spin.y*sin(theta)*sqrt(1-(u*u)) ;
      space.z = (3+ terrain[i][j]/50)*(spin.z*u) ;
      
      space1.x = (3+ terrain[i+1][j+1]/50)*spin.x*cos(theta1)*sqrt(1-(u1*u1)) ;
      space1.y = (3+ terrain[i+1][j+1]/50)*spin.y*sin(theta1)*sqrt(1-(u1*u1));
      space1.z = (3+ terrain[i+1][j+1]/50)*(spin.z*u1) ;
      
      space2.x = (3+ terrain[i+1][j]/50)*spin.x*cos(theta)*sqrt(1-(u1*u1)) ;
      space2.y = (3+ terrain[i+1][j]/50)*spin.y*sin(theta)*sqrt(1-(u1*u1)) ;
      space2.z = (3+ terrain[i+1][j]/50)*(spin.z*u1) ;
      
      space3.x = (3+ terrain[i][j+1]/50)*spin.x*cos(theta1)*sqrt(1-(u*u)) ;
      space3.y = (3+ terrain[i][j+1]/50)*spin.y*sin(theta1)*sqrt(1-(u*u)) ;
      space3.z = (3+ terrain[i][j+1]/50)*(spin.z*u) ;
      
       vertex(space.x, space.y, space.z);
       vertex(space3.x, space3.y, space3.z); 
       vertex(space1.x, space1.y, space1.z);
       vertex(space2.x, space2.y, space2.z); 
     if(colors[j] > colors[j+1] && colors[j] > colors[j+2])
         {
           fill(colors[j]+(terrain[i][j]*2),colors[j+1],colors[j+2]);
         }
     if(colors[j+1] > colors[j] && colors[j+1] > colors[j+2])
         {
           fill(colors[j],colors[j+1]+(terrain[i][j]*2),colors[j+2]);
         }
         else
         {
           fill(colors[j],colors[j+1],colors[j+2]+(terrain[i][j]*2));
         }
    
    }
      endShape();
  }
 }