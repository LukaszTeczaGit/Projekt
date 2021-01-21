#include "HTTPRequest.hpp"
#include <iostream>
#include <fstream>
#include "RSJparser.tcc"

//MUSI BYC DODANY TEN ARGUMENT DO ZBUDOWANIA! -lws2_32

//TODO: Zrobic zabezpieczenie przed tym, ze uzytkownik moze nic nie wpisac i dac po prostu ENTER

std::string API_KEY = "bf6950574cff3222627768d441eb06ed";
std::string cityName = "Warsaw";

bool replace(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int main()
{
    try
    {
        std::cout << "Wpisz nazwe miasta: ";

        std::getline(std::cin, cityName);

        replace(cityName, " ", "%20");

        http::Request request("api.openweathermap.org/data/2.5/weather?units=metric&lang=pl&q=" + cityName + "&appid=" + API_KEY);
        const http::Response response = request.send("GET");
        std::string resultJson = std::string(response.body.begin(), response.body.end()); // print the result

        RSJresource result(resultJson);

        std::string error_code = result["cod"].as<std::string>("default string");

        if (error_code.compare("404") == 0)
        {
            std::cout << "Miasto nie zostało znalezione!";
            return 0;
        }

        //std::cout << result.as<std::string>("default string") << std::endl;

        std::cout << std::endl;
        std::cout << "Miejscowosc: " + result["name"].as<std::string>("default string") << std::endl;
        std::cout << "Pogoda: " + result["weather"][0]["description"].as<std::string>("default string") << std::endl;
        std::cout << "Temperatura: " + result["main"]["temp"].as<std::string>("default string") + " C" << std::endl;
        std::cout << "Temperatura odczuwalna: " + result["main"]["feels_like"].as<std::string>("default string") + " C" << std::endl;
        std::cout << "Temperatura minimalna: " + result["main"]["temp_min"].as<std::string>("default string") + " C" << std::endl;
        std::cout << "Temperatura maksymalna: " + result["main"]["temp_max"].as<std::string>("default string") + " C" << std::endl;
        std::cout << "Chmury: " + result["clouds"]["all"].as<std::string>("default string") + "%" << std::endl;
        std::cout << "Predkosc wiatru: " + result["wind"]["speed"].as<std::string>("default string") + " KM/H" << std::endl;
        std::cout << "Cisnienie: " + result["main"]["pressure"].as<std::string>("default string") + " hPa" << std::endl;
        std::cout << "Wilgotnosc: " + result["main"]["humidity"].as<std::string>("default string") + "%" << std::endl;
        std::cout << "Dlugosc geograficzna: " + result["coord"]["lon"].as<std::string>("default string") << std::endl;
        std::cout << "Szerokosc geograficzna: " + result["coord"]["lat"].as<std::string>("default string") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}