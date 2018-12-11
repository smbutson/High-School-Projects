#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define PI 3.141569

using namespace std;
using namespace sf;

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:



    ParticleSystem(unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(1)),
    m_emitter(0, 0)

    {
    };



    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void setAttractor(sf::Vector2f position)
    {
        attractor = position;
    }

    void update(sf::Time elapsed, int colorChanger, int mode, Vector2f planetposition, Vector2f blackholeposition, Vector2f whaleposition, Vector2f tornadoposition, vector<Vector2i> & attractorList,vector<Vector2i> & repulsorList, vector<int> & freeList)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // update the particle lifetime
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;



            // if the particle is dead, respawn it
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                resetParticle(i);

            }



            // update the position of the corresponding vertex
                float angle = (std::rand() % 360) * 3.14f / 180.f;
                float speed = (std::rand() % 20);
                float planetAngle = 0;
                float planetDistance = 0;
                float blackholeDistance = 0;
                float vectorFinal = 0;


            // detect if particle has reached bounds of screen and bounce if it has
            if(m_vertices[i].position.y >= 900)
            {
                p.velocity = sf::Vector2f(p.velocity.x,-p.velocity.y);
            }
            if(m_vertices[i].position.y <= 0)
            {
                p.velocity = sf::Vector2f(p.velocity.x,-p.velocity.y);
            }
            if(m_vertices[i].position.x >= 1600)
            {
                p.velocity = sf::Vector2f(-p.velocity.x,p.velocity.y);
            }
            if(m_vertices[i].position.x <= 0)
            {
                p.velocity = sf::Vector2f(-p.velocity.x,p.velocity.y);
            }


                m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // change velocity of particle with respect to gravity of attractor
                 if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                angle = atan2(attractor.y-m_vertices[i].position.y,attractor.x-m_vertices[i].position.x);
                acceleration = sf::Vector2f(8*std::cos(angle), 8*std::sin(angle));
                p.velocity += acceleration;
                }
                if(mode == 1 || freeList[0] == 1)
                {
                   angle = atan2(planetposition.y-m_vertices[i].position.y,planetposition.x-m_vertices[i].position.x);
                   acceleration = sf::Vector2f(3*std::cos(angle), 3*std::sin(angle));
                   p.velocity += acceleration;
                }
                if(mode == 1 || freeList[1] == 1)
                {
                   angle = atan2(blackholeposition.y-m_vertices[i].position.y,blackholeposition.x-m_vertices[i].position.x);
                   acceleration = sf::Vector2f(10*std::cos(angle), 10*std::sin(angle));
                   p.velocity += acceleration;
                }
                if(mode == 2 || freeList[3] == 1)
                {
                    angle = atan2(tornadoposition.y-m_vertices[i].position.y,tornadoposition.x-m_vertices[i].position.x);
                    acceleration = sf::Vector2f(7*std::cos(angle), 7*std::sin(angle));
                    p.velocity += acceleration;
                }

                if(mode == 3 || freeList[2] == true)
                {
                   angle = atan2(whaleposition.y-m_vertices[i].position.y,whaleposition.x-m_vertices[i].position.x);
                   acceleration = sf::Vector2f(5*std::cos(angle), 5*std::sin(angle));
                   p.velocity += acceleration;
                }
                if(mode == 4)
                {
                    for(int k = 0; k < attractorList.size(); k++)
                    {
                        angle = atan2(attractorList[k].y-m_vertices[i].position.y,attractorList[k].x-m_vertices[i].position.x);
                        acceleration = sf::Vector2f(5*std::cos(angle), 5*std::sin(angle));
                        p.velocity += acceleration;
                    }
                    for(int j = 0; j < repulsorList.size(); j++)
                    {
                        angle = atan2(repulsorList[j].y-m_vertices[i].position.y,repulsorList[j].x-m_vertices[i].position.x);
                        acceleration = sf::Vector2f(-5*std::cos(angle), -5*std::sin(angle));
                        p.velocity += acceleration;
                    }
                }
                if(colorChanger == 1) {
                m_vertices[i].color = sf::Color(Color::Red);
                }
                if(colorChanger == 2) {
                m_vertices[i].color = sf::Color(Color::Green);
                }
                if(colorChanger == 3) {
                m_vertices[i].color = sf::Color(Color::Blue);
                }
                if(colorChanger == 4) {
                m_vertices[i].color = sf::Color(Color::Yellow);
                }
                if(colorChanger == 5) {
                m_vertices[i].color = sf::Color(Color::White);
                }
                if(colorChanger == 6) {
                m_vertices[i].color = sf::Color(Color::Black);
                }
                if(colorChanger == 7) {
                m_vertices[i].color = sf::Color(Color(rand()%255 + 0,rand()%255 + 0,rand()%255 + 0));
                }
                if(mode == 1 || freeList[0] == 1)
                {
                    planetDistance = sqrt(pow(m_vertices[i].position.x - planetposition.x,2) + pow(m_vertices[i].position.y - planetposition.y,2));
                    if(planetDistance <= 100)
                    {
                        vectorFinal = sqrt(pow(p.velocity.x,2) + pow(p.velocity.y,2));
                        angle = atan2(p.velocity.y,p.velocity.x);
                        planetAngle = atan2(planetposition.y-m_vertices[i].position.y,planetposition.x-m_vertices[i].position.x);

                        if(angle > planetAngle)
                        {
                            angle =  PI + planetAngle - (angle - planetAngle);
                        }
                        else {
                            angle =  PI + planetAngle + (planetAngle - angle);
                        }
                        p.velocity = sf::Vector2f(vectorFinal*std::cos(angle),vectorFinal*std::sin(angle));
                    }
                }
                if(mode == 1 || freeList[1] == 1)
                {
                    blackholeDistance = sqrt(pow(m_vertices[i].position.x - blackholeposition.x,2) + pow(m_vertices[i].position.y - blackholeposition.y,2));
                        if(blackholeDistance <= 64)
                        {
                            m_vertices[i].color = sf::Color(Color(0,0,0,0));
                            m_vertices[i].position = blackholeposition;
                        }
                }



        }
    }

    private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 20) + 10.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, (std::sin(angle) * speed));
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 1000) + 4000);

        // reset the position of the corresponding vertex
        m_vertices[index].position = m_emitter;
        m_vertices[index].color = (sf::Color(rand()%255 + 0,rand()%255 + 0,rand()%255 + 0));
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
    sf::Vector2f attractor;
    sf::Vector2f acceleration;
};


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Particles");

    // create the particle system
    ParticleSystem particles(10000);

        Texture backgroundsheet;
        Texture startbackgroundsheet;
        Sprite background;
        background.setScale(1.2f,1.0f);
        Sprite startbackground;
        Mouse myMouse;
        int mode = 0;
        int i = 0;
        float planetx = 0;
        float planety = 0;
        float blackholex = 0;
        float blackholey = 0;
        float tornadox = 800;
        float tornadoy = 450;
        float c = 1500;
        float cc = 800;
        int colorChange = 0;
        int frame = 0;
        bool addc=false;
        bool addcc=false;
        int j = 0;
        Vector2f planetposition(planetx,planety);
        Vector2f blackholeposition(blackholex,blackholey);
        Vector2f tornadoposition(tornadox,tornadoy);
        Vector2f whaleposition(c,cc);
        Vector2i attractorPoint(0,0);
        Vector2i repulsorPoint (0,0);
        vector<Vector2i> attractorList;
        vector<Vector2i> repulsorList;
        vector<int> freeList;
        freeList.push_back(j);
        freeList.push_back(j);
        freeList.push_back(j);
        freeList.push_back(j);



    // create a clock to track the elapsed time
    sf::Clock clock;

    srand(time(NULL));

        if (!startbackgroundsheet.loadFromFile("ParticleSimulatorFiles/startmenu.jpg"))
            cout << "not loading" << endl;
        startbackground.setTexture(startbackgroundsheet);
        startbackground.setScale(1.4f,1.6f);

        sf::Font font;
    if (!font.loadFromFile("ParticleSimulatorFiles/arial.ttf"))
    {
        // error...
    }
        sf::Text text;
    text.setFont(font);
    text.setString("Particle Simulator by: Simon Butson and Samson DeVol");
    text.setCharacterSize(50);
    text.setColor(sf::Color::White);
    text.setPosition(sf::Vector2f(150,50));
    text.setStyle(sf::Text::Bold);

    sf::Text textspace;
    textspace.setFont(font);
    textspace.setString("Space Setting");
    textspace.setCharacterSize(24);
    textspace.setColor(sf::Color::Black);
    textspace.setPosition(sf::Vector2f(400,300));
    textspace.setStyle(sf::Text::Bold);

    sf::Text textearth;
    textearth.setFont(font);
    textearth.setString("Earth Setting");
    textearth.setCharacterSize(24);
    textearth.setColor(sf::Color::Black);
    textearth.setPosition(sf::Vector2f(1000,300));
    textearth.setStyle(sf::Text::Bold);

    sf::Text textwater;
    textwater.setFont(font);
    textwater.setString("Water Setting");
    textwater.setCharacterSize(24);
    textwater.setColor(sf::Color::Black);
    textwater.setPosition(sf::Vector2f(400,600));
    textwater.setStyle(sf::Text::Bold);

    sf::Text textfree;
    textfree.setFont(font);
    textfree.setString("Free Play");
    textfree.setCharacterSize(24);
    textfree.setColor(sf::Color::Black);
    textfree.setPosition(sf::Vector2f(1000,600));
    textfree.setStyle(sf::Text::Bold);

    sf::RectangleShape spaceButton(sf::Vector2f(120, 50));
    spaceButton.setSize(sf::Vector2f(200, 50));
    spaceButton.setFillColor(sf::Color::White);
    spaceButton.setPosition(400,300);
    spaceButton.setOutlineColor(sf::Color::Red);
    spaceButton.setOutlineThickness(5);

    sf::RectangleShape earthButton(sf::Vector2f(120, 50));
    earthButton.setSize(sf::Vector2f(200, 50));
    earthButton.setFillColor(sf::Color::White);
    earthButton.setPosition(1000,300);
    earthButton.setOutlineColor(sf::Color::Red);
    earthButton.setOutlineThickness(5);

    sf::RectangleShape waterButton(sf::Vector2f(120, 50));
    waterButton.setSize(sf::Vector2f(200, 50));
    waterButton.setFillColor(sf::Color::White);
    waterButton.setPosition(400,600);
    waterButton.setOutlineColor(sf::Color::Red);
    waterButton.setOutlineThickness(5);

    sf::RectangleShape freeButton(sf::Vector2f(120, 50));
    freeButton.setSize(sf::Vector2f(200, 50));
    freeButton.setFillColor(sf::Color::White);
    freeButton.setPosition(1000,600);
    freeButton.setOutlineColor(sf::Color::Red);
    freeButton.setOutlineThickness(5);




    Texture whaleSheet;
    Sprite whaleSprite;
    int frameCounter = 0;
    if (!whaleSheet.loadFromFile("ParticleSimulatorFiles/whale.png")) {
        cout << "not loading" << endl;
    }
        whaleSprite.setTexture(whaleSheet);



     Texture planetsheet;
     Sprite planetsprite;
     if (!planetsheet.loadFromFile("ParticleSimulatorFiles/planet18.png")) {
        cout << "not loading" << endl;
        }
     planetsprite.setTexture(planetsheet);
     planetsprite.setScale(.05f,.05f);
     planetsprite.setPosition(rand()% 1400,rand()% 700);
      Texture blackholesheet;
      Sprite blackholesprite;
        if (!blackholesheet.loadFromFile("ParticleSimulatorFiles/blackhole.png")) {
            cout << "not loading" << endl;
        }
        blackholesprite.setTexture(blackholesheet);
        blackholesprite.setScale(5.0f,5.0f);
        blackholesprite.setPosition(rand() % 1400,rand() % 700);

    sf::Font font2;

    if (!font2.loadFromFile("ParticleSimulatorFiles/adlanta.otf"))
    {
        // error...
    }
        sf::Text controltext;
    controltext.setFont(font2);
    controltext.setString("To open Control Menu hold M");
    controltext.setCharacterSize(12);
    controltext.setColor(sf::Color::White);
    controltext.setPosition(sf::Vector2f(25,25));
    controltext.setStyle(sf::Text::Bold);

       sf::Text controltextmenu;
    controltextmenu.setFont(font2);
    controltextmenu.setString(" For a planet press P \n For a black hole press B \n For a whale press W \n For a tornado Press T \n To change colors press Num 1-5 \n For an attractor point press A \n For a repulsor point press R \n To clear all press LCtrl");
    controltextmenu.setCharacterSize(12);
    controltextmenu.setColor(sf::Color::White);
    controltextmenu.setPosition(sf::Vector2f(50,50));
    controltextmenu.setStyle(sf::Text::Bold);





    window.setFramerateLimit(60);

    int startmenu();

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

            if(mode == 0)
         {
              if(Mouse::isButtonPressed(Mouse::Left)){
                if (spaceButton.getGlobalBounds().contains (myMouse.getPosition(window).x,myMouse.getPosition(window).y)){
                if (!backgroundsheet.loadFromFile("ParticleSimulatorFiles/space-1.jpg")){
                    cout << "not loading" << endl; }
                background.setTexture(backgroundsheet);
                mode = 1;
                colorChange = 4;
                planetx = rand()% 1400;
                planety = rand()% 700;
                planetsprite.setPosition(planetx,planety);
                planetposition = Vector2f(planetx+100,planety+100);
                blackholex = rand()% 1400;
                blackholey = rand()% 700;
                blackholesprite.setPosition(blackholex,blackholey);
                blackholeposition = Vector2f(blackholex+70,blackholey+70);
                }
            }

             if(Mouse::isButtonPressed(Mouse::Left)){
                if (earthButton.getGlobalBounds().contains (myMouse.getPosition(window).x,myMouse.getPosition(window).y)){
                if (!backgroundsheet.loadFromFile("ParticleSimulatorFiles/field.jpg")) {
                            cout << "not loading" << endl; }
                background.setTexture(backgroundsheet);
                  mode = 2;
                  colorChange = 2;

                }
            }


             if(Mouse::isButtonPressed(Mouse::Left)){
                if (waterButton.getGlobalBounds().contains (myMouse.getPosition(window).x,myMouse.getPosition(window).y)){
                    if (!backgroundsheet.loadFromFile("ParticleSimulatorFiles/Research Oceans.jpg")) {
                        cout << "not loading" << endl; }
                background.setTexture(backgroundsheet);
                  mode = 3;
                  colorChange = 3;

                }
            }


             if(Mouse::isButtonPressed(Mouse::Left)){
                if (freeButton.getGlobalBounds().contains (myMouse.getPosition(window).x,myMouse.getPosition(window).y)){
                if (!backgroundsheet.loadFromFile("ParticleSimulatorFiles/black-background.jpg")) {
                        cout << "not loading" << endl; }
                background.setTexture(backgroundsheet);
                  mode = 4;
                  colorChange = 1;
            }
          }

         }

         // keyboard commands to change color of particles

         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
         {
             colorChange = 1;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
         {
             colorChange = 2;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
         {
             colorChange = 3;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
         {
             colorChange = 4;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
         {
             colorChange = 5;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
         {
             colorChange = 6;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
         {
             colorChange = 7;
         }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
         {
             mode = 0;
             backgroundsheet.loadFromFile("ParticleSimulatorFiles/startmenu.jpg");
             background.setTexture(backgroundsheet);
             attractorList.clear();
             repulsorList.clear();
             freeList[0] = 0;
             freeList[1] = 0;
             freeList[2] = 0;
             freeList[3] = 0;
         }



        if(mode == 3 || freeList[2] == 1)
        {
            whaleSprite.setTextureRect(IntRect(4,18*frame,24,18));
            whaleSprite.setScale(10.0f,10.0f);
            whaleSprite.setPosition(c,cc);
            if (c<=30){
                addc=true;
            }
            if (c>=1300){
                addc=false;
            }
            if (addc==true){
                whaleSprite.setTextureRect(IntRect(28,18*frame,48,18));
                c = c + 5;
            }
            if (addc==false){
                whaleSprite.setTextureRect(IntRect(4,18*frame,24,18));
                c = c - 5;
            }
            if (cc<=30){
                addcc=true;
            }
            if (cc>=800){
                addcc=false;
            }
            if (addcc==true){
                cc = cc + 5;
            }
            if (addcc==false){
                cc = cc -5;
            }
            if(frameCounter == 10){
            frame = (frame + 1) %3;
            frameCounter = 0;
            }
            frameCounter++;
            whaleposition = Vector2f(c,cc);

        }


        // make the particle system emitter follow the mouse

        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            particles.setEmitter(window.mapPixelToCoords(mouse));

        }

        // set an attractor point for the particles

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            particles.setAttractor(window.mapPixelToCoords(mouse));
        }



        // update it
         sf::Time elapsed = clock.restart();
         particles.update(elapsed,colorChange,mode,planetposition,blackholeposition,whaleposition,tornadoposition,attractorList,repulsorList,freeList);

        // draw it
        window.clear();

        window.draw(background);
        if(mode == 0)
        {
            window.draw(startbackground);
            window.draw(spaceButton);
            window.draw(earthButton);
            window.draw(waterButton);
            window.draw(freeButton);
            window.draw(text);
            window.draw(textspace);
            window.draw(textearth);
            window.draw(textwater);
            window.draw(textfree);
        }
        if(mode == 1 || freeList[0] == true)
        {
            window.draw(planetsprite);
        }
        if(mode == 1 || freeList[1] == true)
        {
            window.draw(blackholesprite);
        }
        if(mode == 2 || freeList[3] == true)
        {
            i++;
            if(i < 360)
            {
                tornadox = 50*std::cos((i*PI)/180) + 800;
                tornadoy = 10*std::sin((i*PI)/180) + 450;
            }
            else{
                i = 0;
            }
            tornadoposition = Vector2f(tornadox,tornadoy);
        }

        if(mode == 3 || freeList[2] == true)
        {
            window.draw(whaleSprite);
        }

        if(mode == 4)
        {
            window.draw(controltext);
            if(sf::Keyboard::isKeyPressed(Keyboard::A))
            {
                attractorPoint = sf::Mouse::getPosition(window);
                attractorList.push_back(attractorPoint);
            }
            if(sf::Keyboard::isKeyPressed(Keyboard::R))
            {
                repulsorPoint = sf::Mouse::getPosition(window);
                repulsorList.push_back(repulsorPoint);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
             window.draw(controltextmenu);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                planetsprite.setPosition(mouse.x-100,mouse.y-100);
                planetposition = Vector2f(mouse.x,mouse.y);
                window.draw(planetsprite);
                freeList[0] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                blackholesprite.setPosition(mouse.x-70,mouse.y-70);
                blackholeposition = Vector2f(mouse.x,mouse.y);
                window.draw(blackholesprite);
                freeList[1] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                c = mouse.x;
                cc = mouse.y;
                whaleSprite.setPosition(c,cc);
                whaleposition = Vector2f(c,cc);
                window.draw(whaleSprite);
                freeList[2] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                tornadoposition = Vector2f(mouse.x,mouse.y);
                freeList[3] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                freeList[0] = 0;
                freeList[1] = 0;
                freeList[2] = 0;
                freeList[3] = 0;
                attractorList.clear();
                repulsorList.clear();
            }
        }

        if(mode != 0){
            window.draw(particles);
        }
        window.display();
    }

    return 0;
}



