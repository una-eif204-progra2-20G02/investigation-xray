//
// Created by Maikol Guzman on 9/28/20.
//

#include <../lib/nlohmann/json.hpp>
#include <iostream>

using namespace std;
using json = nlohmann::json;

struct Persona {
    string nombre;
    int edad;
    int id;

    Persona() {}

    Persona(const string &nombre, int edad, int id) : nombre(nombre), edad(edad), id(id) {}

    const string &getNombre() const {
        return nombre;
    }

    void setNombre(const string &nombre) {
        Persona::nombre = nombre;
    }

    int getEdad() const {
        return edad;
    }

    void setEdad(int edad) {
        Persona::edad = edad;
    }

    int getId() const {
        return id;
    }

    void setId(int id) {
        Persona::id = id;
    }
};

int main() {

    /*
     * Ejemplo de una serialización del objeto Persona
     * https://github.com/nlohmann/json

     {
        "nombre": "Ned Flanders",
        "edad": 18,
        "id" : 60
     }

     */

    Persona persona1 = {"Ned Flanders", 18, 60};

    // Convertir a JSON: Copia cada valor en un objeto JSON (SERIALIZACION)
    json jsonPersona;
    jsonPersona["nombre"] = persona1.getNombre();
    jsonPersona["edad"] = persona1.getEdad();
    jsonPersona["id"] = persona1.getId();

    string personaSerializado = jsonPersona.dump();

    // Convertir desde JSON: copia cada valor desde un objeto de JSON (DESEREALIZAR)
    Persona persona2;
    persona2.setNombre(jsonPersona["nombre"]);
    persona2.setEdad(jsonPersona["edad"]);
    persona2.setId(jsonPersona["id"]);

    // Convertir de un String de JSON (DESEREALIZAR)
    string data = R"({
                        "nombre": "Ned Flanders",
                        "edad": 18,
                        "id" : 60
                    })";

    json jsonData = json::parse(data);
    Persona persona3;
    persona3.setNombre(jsonData["nombre"]);
    persona3.setEdad(jsonData["edad"]);
    persona3.setId(jsonData["id"]);

    std::cout << "Hello, Universidad Nacional!" << std::endl;

    std::cout << "Persona 1: " << persona1.nombre << std::endl;
    std::cout << "Persona 2: " << persona2.nombre << std::endl;
    std::cout << "Persona 3: " << persona3.nombre << std::endl;

    std::cout << "Persona 1 - Serializado en JSON: " << personaSerializado << std::endl;

    return 0;
}