//
// Created by deine on 9/21/2020.
//
#include <iostream>
#include <sstream>
#include <fstream> //usar las funciones de escritura y lectura
#include <vector>
#include "json.hpp"

/*este ejemplo se basa en la publicacion de Daniel Gómez Vergel:
Reflexión estática y serialización de agregados en JSON*/

using namespace std;

struct Persona {

    string nombre;
    int edad;
    int id;

    Persona() = default;

    Persona(string nombre, int edad, int id) : nombre(nombre), edad(edad), id(id) {}
};

/*struct PersonaList{
    vector<Persona> personasList;

    void insertarPersona(Persona persona)
    {
        personasList.push_back(persona);
    }

    Persona consultarPorPosicion(int pos)
    {
        return personasList.operator[](pos);
    }

};*/

auto to_json(nlohmann::json& json, Persona const& persona) -> void
{
    json = nlohmann::json{
            {"nombre: ", persona.nombre},
            {"Edad: ", persona.edad},
            {"id: ", persona.id}
    };
}

auto from_json(nlohmann::json const& json, Persona const& persona) -> void
{
    json.at("Nombre: ").get_to(persona.nombre);
    json.at("Edad: ").get_to(persona.edad);
    json.at("Id: ").get_to(persona.id);
}

/*void guardar(Persona persona) {
    ofstream archivo;
    try { archivo.open("ArchivoTexto.txt", ios::app); }
    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    archivo << persona->toString() << endl;
    archivo.close();
}

void leer() {
    ifstream archivo;
    string texto;
    try { archivo.open("ArchivoTexto.txt", ios::in); }
    catch (std::ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    cout << endl;
    while (!archivo.eof()) {
        getline(archivo, texto);
        cout << texto << endl;
    }
    archivo.close();
}*/

int main() {

/*PersonaList personasList =  PersonaList();
personasList.insertarPersona(p1);
personasList.insertarPersona(p2);
personasList.insertarPersona(p3);
personasList.insertarPersona(p4);*/

    Persona p1 =  Persona("Luis", 23, 1);
    Persona p2 = Persona("Christofer", 19, 2);
    Persona p3 = Persona("Deiner", 43, 3);
    Persona p4 = Persona("Maikol", 45, 4);

auto const personas = vector<Persona>{ p1, p2, p3, p4 };

    if (auto ofs = ofstream{"persona.jsonl", std::ios::binary}){
        for (auto const& persona : personas)
        ofs << nlohmann::json(persona) << '\n'; // conversión Persona-->json
    } else {
        cout<< "no se pudo abrir el archivo\n";
    }

    //    La invocación j.get<Persona>() --que llama implícitamente a la función from_json()--
//    retorna finalmente el objeto Persona a insertar al fondo del vector.

    auto persona = vector<Persona>{}; // vector inicialmente vacío

    if (auto ifs = ifstream{"persona.jsonl", std::ios::binary}) {
        auto json_line = string{};
        while (getline(ifs, json_line)) { // parseamos el fichero línea a línea
            auto const j = nlohmann::json::parse(json_line);
            persona.push_back(j.get<Persona>()); // conversión json-->Persona
        }
    } else {
        cout << "no se pudo abrir el archivo\n";
    }
    return 0;
};
