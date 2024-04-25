#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <experimental/random>
#include <list>
#include <fstream>


using namespace std;
using namespace ftxui;

int main(int argc, char const *argv[])
{
    fstream imagen;
    list<string> textos;
    string linea;

    imagen.open("./assets/imagen.txt");
    
    while (getline(imagen, linea))
    {
        textos.push_back(linea);
    }
    imagen.close();

    int posX = 0;
    int posY = 1;
    int fotograma = 0;
    string reset;

    while (true)
    {
        fotograma++;

        int R = std::experimental::randint(0, 255);
        int G = std::experimental::randint(0, 255);
        int B = std::experimental::randint(0, 255);

        Element personaje = spinner(21, fotograma);
        Decorator colorFondo = bgcolor(Color::RGB(R, G, B));
        Decorator colorTexto = color(Color::RGB(B, G, R));
        Element dibujo = border({hbox() | colorFondo | colorTexto});

        // Crear dimensiones de pantalla
        Dimensions Alto = Dimension::Full();
        Dimensions Ancho = Dimension::Full();

        // Crear pantalla
        Screen pantalla = Screen::Create(Ancho, Alto);

        // Imprimir en la pantalla
        Render(pantalla, dibujo);
        
        int l = 0;
        for (auto &&texto : textos)
        {
            int i = 0;
            for (auto &&letra : texto)
            {
                pantalla.PixelAt(posX + i, posY + l).character = letra;
                i++;
            }
            l++;
        }

        posX++;
        pantalla.Print();

        // Resetear pantalla
        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.1s);
    }

    return 0;
}
