//
// Created by Maikol Guzman on 9/28/20.
//

#include <../lib/nlohmann/json.hpp>
#include <iostream>
#include <fstream>

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
  /*  Persona persona2 = {"pep", 22, 43};
    Persona persona3 = {"lucas", 33, 12};*/

    // Convertir a JSON: Copia cada valor en un objeto JSON (SERIALIZACION)
    json jsonPersona;
    jsonPersona["nombre"] = persona1.getNombre();
    jsonPersona["edad"] = persona1.getEdad();
    jsonPersona["id"] = persona1.getId();

    string personaSerializado = jsonPersona.dump(4);

/*
    //SERIALIZANDO UNA LISTA.

 */
/*agrega otro objeto (usando una lista inicializadora)
 j [ " objeto " ] = {{ " moneda " , " USD " }, { " valor " , 42,99 }};*//*


   json jsonPersonas;

jsonPersonas["Personas"] = {{" Persona 1: ",persona1.getNombre(),persona1.getEdad(),persona1.getId()},
                            {" Persona 2: ",persona2.getNombre(),persona2.getEdad(),persona2.getId()},
                            {" Persona 3: ",persona3.getNombre(),persona3.getEdad(),persona3.getId()}};

string personasSerializando = jsonPersonas.dump();

*/


    // Convertir desde JSON: copia cada valor desde un objeto de JSON (DESEREALIZAR)
    Persona persona22;
    persona22.setNombre(jsonPersona["nombre"]);
    persona22.setEdad(jsonPersona["edad"]);
    persona22.setId(jsonPersona["id"]);

    // Convertir de un String de JSON (DESEREALIZAR)
    string data = R"({
                        "nombre": "Ned Flanders",
                        "edad": 18,
                        "id" : 60
                    })";

    json jsonData = json::parse(data);
    Persona persona33;
    persona33.setNombre(jsonData["nombre"]);
    persona33.setEdad(jsonData["edad"]);
    persona33.setId(jsonData["id"]);


    //guarda el archivo
    ofstream archivo;
    try { archivo.open("ArchivoTexto.json", ios::binary); }
    catch (ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    //para la lista de personas poner:archivo << personasSerializando<< '\n';
    archivo << personaSerializado << '\n';
    archivo.close();

    //lee el archivo
    ifstream archivo1;
    string texto;
    try { archivo1.open("ArchivoTexto.json", ios::binary); }
    catch (ifstream::failure a) {
        cout << "no se pudo abrir el archivo";
        exit(1);
    }
    cout << endl;
    while (!archivo1.eof()) {
        getline(archivo1, texto);
        cout << texto << endl;
    }
    archivo1.close();


    return 0;
}