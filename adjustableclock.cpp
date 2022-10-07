#include <chrono>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

double besttime() {
  auto now = chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count()/1'000'000'000.0;
}

tm time_adjust(time_t time, int adjust) {
  time += adjust;
  return *localtime(&time);
}

int main(int argc, char* argv[]) {
    float second = 60;

    int clock_offset = 0;
    
	if (argc > 1) {
        clock_offset = stoi(argv[1]);
    }

    sf::RenderWindow window(sf::VideoMode(200,200), "12345@bu.edu");

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    
  sf::RectangleShape houd_hand;
  houd_hand.setPosition(100, 100);
  houd_hand.setSize(sf::Vector2f(70, 3.0f));
  houd_hand.setFillColor(sf::Color::Green);
  sf::RectangleShape minute_hand;
  minute_hand.setPosition(100, 100);
  minute_hand.setSize(sf::Vector2f(80, 2.0f));
  minute_hand.setFillColor(sf::Color::Blue);
  sf::RectangleShape second_hand;
  second_hand.setPosition(100, 100);
  second_hand.setSize(sf::Vector2f(90, 1.0f));
  second_hand.setFillColor(sf::Color::Red);

  while (window.isOpen()) {
    
    sf::Event Event;
    while (window.pollEvent(Event)) {
      if (Event.type == sf::Event::Closed) {
        window.close();
      }
    }

    time_t offset_time = std::time(NULL) + clock_offset;
    tm now = *localtime(&offset_time);

    time_t current_time = std::time(NULL);
    tm adjusted_time;  
    double accurate_time = besttime(); 


    sf::Text digital_time;
    digital_time.setFont(font);
    digital_time.setFillColor(sf::Color::White);
    
    digital_time.setCharacterSize(15);
    digital_time.setOutlineThickness(1);
    digital_time.setPosition(75, 5);
    
    if ((accurate_time - (int)accurate_time) < 0.25) {
    
      adjusted_time = time_adjust(current_time, clock_offset);
      string terminal_time = asctime(&adjusted_time);
      digital_time.setString(terminal_time.substr(11, 8));
    

    float temp = second;
    second = now.tm_sec;

    houd_hand.setRotation((now.tm_hour / 12.0f) * 360.0f - 90.0f);
    minute_hand.setRotation((now.tm_min / 60.0f) * 360.0f - 90.0f);
    second_hand.setRotation((now.tm_sec / 60.0f) * 360.0f - 90.0f);

    if (temp != second) {
      cout << asctime(localtime(&offset_time)) << endl;
    }

    window.clear();
    window.draw(houd_hand);
    window.draw(minute_hand);
    window.draw(second_hand);
    window.draw(digital_time);
    window.display();
    }
  }
}
