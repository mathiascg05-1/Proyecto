// PROYECTO ZOMBIES REALIZADO POR CARSTENS, MATHIAS; LUCA, FRANCO; Becerra, Nicole.
// C.I. 31.046.461; 31.790.135

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <cstdlib>
using namespace std;


// Estructura para representar un Zombie
struct Zombie {
    string nombre;
    int fortaleza;
    int ataque;

    Zombie(string n, int f, int a) : nombre(n), fortaleza(f), ataque(a) {}
};
// Gestion Accesorios: permite Agregar, Modificar, Eliminar accesorios, asi como tambien buscar toda la informacion asociada a los mismos.
struct Armas {
    string nombre;
    int num_arma;
    string tipo_de_arma;
    int con_municion_o_cuerpo_cuerpo; // las que usan municion se toman como tipo 1, y si se usan una vez y ya se toman como tipo 2
    int dano;
    int municion;

    Armas(string n, int na, string tda, int cm_cc, int d, int m) 
        : nombre(n), num_arma(na), tipo_de_arma(tda), con_municion_o_cuerpo_cuerpo(cm_cc), dano(d), municion(m) {}
};

struct Defensa {
    string nombre;
    int dano_defendido;
    int refuerzo;

    Defensa(string n, int d_d, int r) 
        : nombre(n), dano_defendido(d_d), refuerzo(r) {}
};

struct Curacion {
    string nombre;
    int vida_recuperada;
    int usos;

    Curacion(string n, int v_r, int u) 
        : nombre(n), vida_recuperada(v_r), usos(u) {}
};

// Gestion Mochila:
struct Mochila {
    Armas* arma;      // Usar puntero para Armas
    Defensa* defensa; // Usar puntero para Defensa
    Curacion* curacion; // Usar puntero para Curacion

    Mochila() : arma(nullptr), defensa(nullptr), curacion(nullptr) {}

};

// Funcion para agregar un arma a la mochila
void agregarArma(Mochila* mochila, Armas* armaSeleccionada) {
    if (mochila->arma == nullptr) { // Verificar si el campo arma esta vacio
        mochila->arma = armaSeleccionada;
        cout << "Arma agregada: " << armaSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay un arma en la mochila. No se puede agregar: " << armaSeleccionada->nombre << endl;
        delete armaSeleccionada; // Liberar el arma seleccionada si no se agrega
    }
}

// Funcion para seleccionar un arma
Armas* seleccionarYAgregarArma(Mochila* mochila) {
    Armas* armas[7] = {
        new Armas("Pistola", 1, "Arma de fuego", 1, 25, 15),
        new Armas("Fusil de Asalto", 2, "Arma de fuego", 1, 30, 30),
        new Armas("Coctel Molotov", 3, "Arma arrojadiza", 1, 60, 2),
        new Armas("Cuchillo", 4, "Arma blanca", 2, 15, 100),
        new Armas("Tuberia", 5, "Arma contundente", 2, 20, 60),
        new Armas("Liquido inflamable", 6, "Arma incendiaria", 2, 70, 1),
        new Armas("Trampa de caida", 7, "Trampa", 2, 90, 1)
    };

    int opcion;
    cout << "Selecciona un arma:\n";
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << ". " << armas[i]->nombre << endl;
    }
    cout << "Elige una opcion (1-7): ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 7) {
        // Si ya hay un arma en la mochila, eliminarla
        if (mochila->arma != nullptr) {
            cout << "Reemplazando arma: " << mochila->arma->nombre << endl;
            delete mochila->arma; // Liberar la memoria del arma existente
        }
        mochila->arma = armas[opcion - 1]; // Asignar el nuevo arma
        cout << "Arma seleccionada: " << mochila->arma->nombre << endl;

        // Liberar la memoria de las armas que no fueron seleccionadas
        for (int i = 0; i < 7; i++) {
            if (i != opcion - 1) {
                delete armas[i];
            }
        }
        return mochila->arma; // Retornar el puntero al arma seleccionada
    } else {
        cout << "Opcion no valida" << endl;
        // Liberar la memoria de todas las armas
        for (int i = 0; i < 7; i++) {
            delete armas[i];
        }
        return nullptr; // Retornar nullptr si la opcion no es valida
    }
}


// Funcion para mostrar las armas
void mostrarArmas(Armas* armas[], int cantidad) {
    cout << "Armas disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << armas[i]->nombre
             << ", Tipo: " << armas[i]->tipo_de_arma 
             << ", Dano: " << armas[i]->dano 
             << ", Municion: " << armas[i]->municion << ")\n";
    }
}

// Funcion para agregar una defensa a la mochila
void agregarDefensa(Mochila* mochila, Defensa* defensaSeleccionada) {
    if (mochila->defensa == nullptr) { // Verificar si el campo defensa esta vacio
        mochila->defensa = defensaSeleccionada;
        cout << "Defensa agregada: " << defensaSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay una defensa en la mochila. No se puede agregar: " << defensaSeleccionada->nombre << endl;
        delete defensaSeleccionada; // Liberar la defensa seleccionada si no se agrega
    }
}

Defensa* seleccionarYAgregarDefensa(Mochila* mochila) {
    Defensa* defensas[4] = {
        new Defensa("Chaleco antizombies", 50, 100),
        new Defensa("Escudo", 30, 150),
        new Defensa("Casco de moto", 20, 80),
        new Defensa("Armadura pesada", 70, 200)
    };

    int opcion;
    cout << "Selecciona una defensa:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << defensas[i]->nombre << endl;
    }
    cout << "Elige una opcion (1-4): ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        // Si ya hay una defensa en la mochila, eliminarla
        if (mochila->defensa != nullptr) {
            cout << "Reemplazando defensa: " << mochila->defensa->nombre << endl;
            delete mochila->defensa; // Liberar la memoria de la defensa existente
        }
        mochila->defensa = defensas[opcion - 1]; // Asignar la nueva defensa
        cout << "Defensa seleccionada: " << mochila->defensa->nombre << endl;

        // Liberar la memoria de las defensas que no fueron seleccionadas
        for (int i = 0; i < 4; i++) {
            if (i != opcion - 1) {
                delete defensas[i];
            }
        }
        return mochila->defensa; // Retornar el puntero a la defensa seleccion ada
    } else {
        cout << "Opcion no valida" << endl;
        // Liberar la memoria de todas las defensas
        for (int i = 0; i < 4; i++) {
            delete defensas[i];
        }
        return nullptr; // Retornar nullptr si la opcion no es valida
    }
}


void mostrarDefensas(Defensa* defensas[], int cantidad) {
    cout << "Defensas disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << defensas[i]->nombre
            << ", Dano defendido: " << defensas[i]->dano_defendido 
            << ", Durabilidad: " << defensas[i]->refuerzo << endl;
    }
}

// Funcion para agregar una curacion a la mochila
void agregarCuracion(Mochila* mochila, Curacion* curacionSeleccionada) {
    if (mochila->curacion == nullptr) { // Verificar si el campo curacion esta vacio
        mochila->curacion = curacionSeleccionada;
        cout << "Curacion agregada: " << curacionSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay una curacion en la mochila. No se puede agregar: " << curacionSeleccionada->nombre << endl;
        delete curacionSeleccionada; // Liberar la curacion seleccionada si no se agrega
    }
}

Curacion* seleccionarYAgregarCuracion(Mochila* mochila) {
    Curacion* curaciones[4] = {
        new Curacion("Vendas", 20, 5),
        new Curacion("Botiquin", 50, 3),
        new Curacion("Antidoto experimental", 30, 2),
        new Curacion("Suero de supervivencia", 15, 10)
    };

    int opcion;
    cout << "Selecciona una curacion:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << curaciones[i]->nombre << endl;
    }
    cout << "Elige una opcion (1-4): ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        // Si ya hay una curacion en la mochila, eliminarla
        if (mochila->curacion != nullptr) {
            cout << "Reemplazando curacion: " << mochila->curacion->nombre << endl;
            delete mochila->curacion; // Liberar la memoria de la curacion existente
        }
        mochila->curacion = curaciones[opcion - 1]; // Asignar la nueva curacion
        cout << "Curacion seleccionada: " << mochila->curacion->nombre << endl;

        // Liberar la memoria de las curaciones que no fueron seleccionadas
        for (int i = 0; i < 4; i++) {
            if (i != opcion - 1) {
                delete curaciones[i];
            }
        }
        return mochila->curacion; // Retornar el puntero a la curacion seleccionada
    } else {
        cout << "Opcion no valida" << endl;
        // Liberar la memoria de todas las curaciones
        for (int i = 0; i < 4; i++) {
            delete curaciones[i];
        }
        return nullptr; // Retornar nullptr si la opcion no es valida
    }
}


void mostrarCuraciones(Curacion* curaciones[], int cantidad) {
    cout << "Curaciones disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << curaciones[i]->nombre
             << ", Vida recuperada: " << curaciones[i]->vida_recuperada 
             << ", Cantidad de usos: " << curaciones[i]->usos << endl;
    }
}

// Funcion para eliminar un arma
void eliminarArma(Mochila* mochila) {
    if (mochila->arma) {
        cout << "Eliminando arma: " << mochila->arma->nombre << endl;
        delete mochila->arma;
        mochila->arma = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay arma para eliminar.\n";
    }
}

// Funcion para eliminar una defensa
void eliminarDefensa(Mochila* mochila) {
    if (mochila->defensa) {
        cout << "Eliminando defensa: " << mochila->defensa->nombre << endl;
        delete mochila->defensa;
        mochila->defensa = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay defensa para eliminar.\n";
    }
}

// Funcion para eliminar una curacion
void eliminarCuracion(Mochila* mochila) {
    if (mochila->curacion) {
        cout << "Eliminando curacion: " << mochila->curacion->nombre << endl;
        delete mochila->curacion;
        mochila->curacion = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay curacion para eliminar.\n";
    }
}

void mostrarMochila(const Mochila& mochila) {
    if (mochila.arma != nullptr) {
        cout << "Arma: " << mochila.arma->nombre << endl;
        cout << "Numero de arma: " << mochila.arma->num_arma << endl;
        cout << "Tipo de arma: " << mochila.arma->tipo_de_arma << endl;
        cout << "Con municion o cuerpo a cuerpo: " << mochila.arma->con_municion_o_cuerpo_cuerpo << endl;
        cout << "Dano: " << mochila.arma->dano << endl;
        cout << "Municion: " << mochila.arma->municion << endl;
    }

    if (mochila.defensa != nullptr) {
        cout << "Defensa: " << mochila.defensa->nombre << endl;
        cout << "Dano defendido: " << mochila.defensa->dano_defendido << endl;
        cout << "Refuerzo: " << mochila.defensa->refuerzo << endl;
    }

    if (mochila.curacion != nullptr) {
        cout << "Curacion: " << mochila.curacion->nombre << endl;
        cout << "Vida recuperada: " << mochila.curacion->vida_recuperada << endl;
        cout << "Usos: " << mochila.curacion->usos << endl;
    }
}

void opcionesEliminacionMochila(Mochila* mochila) {
    int opcion;
    mostrarMochila(*mochila);
    
    cout << "¿Que deseas eliminar?\n";
    cout << "1. Arma\n";
    cout << "2. Defensa\n";
    cout << "3. Curacion\n";
    cout << "Elige una opcion (1-3): ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            eliminarArma(mochila);
            break;
        case 2:
            eliminarDefensa(mochila);
            break;
        case 3:
            eliminarCuracion(mochila);
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
    }
}

// Gestion de equipos:
struct Soldado {
    string nombre;
    int salud;
    Mochila mochila;

    Soldado(const string& nombre, int salud, const Mochila& mochila)
        : nombre(nombre), salud(salud), mochila(mochila) {}
};

struct Equipo {
    string nombreEquipo;
    vector<Soldado> soldados;

    void agregarSoldado(const Soldado& soldado) {
        soldados.push_back(soldado);
    }

    void mostrarEquipo() const {
        cout << "Equipo:\n";
        for (const auto& soldado : soldados) {
            cout << "Soldado: " << soldado.nombre << ", Salud: " << soldado.salud << "\n";
            cout << "Arma: " << soldado.mochila.arma->nombre << ", Defensa: " << soldado.mochila.defensa->nombre << ", Curacion: " << soldado.mochila.curacion->nombre << "\n";
            cout << "-------------------\n";
        }
    }
};

// Estructura para representar una Estacion
struct Estacion {
    string nombreEstacion;
    int numZombies;
    vector<Zombie> zombies;
    Equipo equipo;
    Estacion* siguiente;
};

// Funcion para verificar si la lista de estaciones esta vacia
bool estaVacio(Estacion* lista) {
    return lista == nullptr;
}

void mostrarEstacionesConS(Estacion* estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    int i = 0;
    while (estaciones != nullptr) {
        cout<<endl<< i << ". " << estaciones->nombreEstacion << endl;

        // Mostrar informacion del equipo en la estacion
        cout << "    Soldados en esta estacion: " << endl;
        if (!estaciones->equipo.soldados.empty()) {
            for (const Soldado& soldado : estaciones->equipo.soldados) {
                cout << "        Soldado: " << soldado.nombre << endl;

                // Mostrar la mochila del soldado
                if (soldado.mochila.arma != nullptr) {
                    cout << "            Arma: " << soldado.mochila.arma->nombre << endl;
                } else {
                    cout << "            Arma: Ninguna" << endl;
                }

                if (soldado.mochila.defensa != nullptr) {
                    cout << "            Defensa: " << soldado.mochila.defensa->nombre << endl;
                } else {
                    cout << "            Defensa: Ninguna" << endl;
                }

                if (soldado.mochila.curacion != nullptr) {
                    cout << "            Curacion: " << soldado.mochila.curacion->nombre << endl;
                } else {
                    cout << "            Curacion: Ninguna" << endl;
                }

                cout << endl; // Linea en blanco entre soldados
            }
        } else {
            cout << "        No hay soldados en esta estacion." << endl;
        }

        estaciones = estaciones->siguiente; // Avanzar al siguiente nodo
        i++;
    }
}

// Funcion para mostrar las estaciones
void mostrarEstacionesConZ(Estacion* estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    int i = 0;
    while (estaciones != nullptr) {
        cout << i << ". " << estaciones->nombreEstacion << endl;
        cout << "    Numero de zombies: " << estaciones->numZombies << endl;

        // Mostrar informacion de los zombies en la estacion
        for (const Zombie& z : estaciones->zombies) {
            cout << "        " << z.nombre << " - Fortaleza: " << z.fortaleza << ", Ataque: " << z.ataque << endl;
        }
        estaciones = estaciones->siguiente;
        i++;
    }
}

// Funcion para crear una nueva estacion
void crearEstacion(Estacion*& estaciones) {
    Estacion* nuevaEstacion = new Estacion();
    cout << "Ingrese el nombre de la estacion: ";
    cin >> nuevaEstacion->nombreEstacion;
    cout << "Ingrese el numero de zombies a agregar: ";
    cin >> nuevaEstacion->numZombies;

    nuevaEstacion->siguiente = nullptr; // Inicializar el puntero siguiente a nullptr

    for (int i = 0; i < nuevaEstacion->numZombies; i++) {
        int tipo;
        cout << "Zombie numero " << i + 1 << " - Seleccione el tipo de zombie:\n";
        cout << "1. Rapido y agil\n";
        cout << "2. Tanque\n";
        cout << "3. Inteligente\n";
        cout << "4. Infectado por Hongos\n";
        cout << "5. Bioluminiscente\n";
        cout << "Ingrese el numero del tipo de zombie que desea agregar: ";
        cin >> tipo;
        cout<<endl;

        // Validar tipo de zombie
        if (tipo < 1 || tipo > 5) {
            cout << "Tipo de zombie desconocido. Por favor, intente de nuevo.\n";
            i--; // Decrementar i para volver a preguntar
            continue;
        }

        // Crear el zombie y agregarlo al vector de la estacion
        switch (tipo) {
            case 1: nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80)); break;
            case 2: nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30)); break;
            case 3: nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60)); break;
            case 4: nuevaEstacion->zombies.push_back(Zombie("Infectado por Hongos", 40, 50)); break;
            case 5: nuevaEstacion->zombies.push_back(Zombie("Bioluminiscente", 60, 70)); break;
        }
    }

    // Insertar la nueva estacion en la lista
    if (estaVacio(estaciones)) {
        nuevaEstacion->siguiente = estaciones;
        estaciones = nuevaEstacion;
        cout << "Estacion '" << nuevaEstacion->nombreEstacion << "' agregada a la lista." << endl;
    } else {
        // Preguntar por la posicion para insertar
        mostrarEstacionesConZ(estaciones);
        int posicion;
        cout << "Ingrese la posicion para insertar la nueva estacion (0 para inicio, si el indice es mayor al ultimo de la lista, se ingresara al final): ";
        cin >> posicion;

        // Validar posicion
        if (posicion < 0) {
            cout << "Posicion no valida. Insertando al inicio." << endl;
            posicion = 0;
        }

        Estacion* actual = estaciones;
        if (posicion == 0) {
            nuevaEstacion->siguiente = estaciones;
            estaciones = nuevaEstacion;
        } else {
            for (int i = 0; i < posicion - 1 && actual->siguiente != nullptr; i++) {
                actual = actual->siguiente;
            }
            nuevaEstacion->siguiente = actual->siguiente;
            actual->siguiente = nuevaEstacion;
        }

        cout << "Estacion '" << nuevaEstacion->nombreEstacion << "' insertada en la posicion " << posicion << "." << endl;
    }
}


// Funcion para eliminar una estacion
void eliminarEstacion(int pos, Estacion*& estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista esta vacia."<<endl;
        return;
    }

    Estacion* aux = estaciones;
    Estacion* eliminar = nullptr;

    if (pos == 0) { // Eliminar la primera estacion
        eliminar = estaciones;
        estaciones = estaciones->siguiente;
    } else {
        for (int i = 0; i < pos - 1 && aux->siguiente != nullptr; i++) {
            aux = aux->siguiente;
        }
        if (aux->siguiente == nullptr) {
            cout << "Posicion no valida." << endl;
            return;
        }
        eliminar = aux->siguiente;
        aux->siguiente = eliminar->siguiente;
    }

    delete eliminar;
}

// Funcion para liberar la memoria de todas las estaciones
void liberarEstaciones(Estacion*& estaciones) {
    Estacion* aux;
    while (estaciones != nullptr) {
        aux = estaciones; // Guardar la estacion actual
        estaciones = estaciones->siguiente; // Mover a la siguiente estacion
        delete aux; // Liberar la memoria de la estacion actual
    }
}

void mostrarEquiposPorEstacion(Estacion* estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    int i = 0;
    while (estaciones != nullptr) {
        cout<<endl<<i << ". Estacion: " << estaciones->nombreEstacion << endl;
        cout << "  * Numero de Zombies: " << estaciones->numZombies << endl;

        // Mostrar soldados en el equipo de la estacion
        cout << "   * Soldados en esta estacion: " << endl;
        for (const Soldado& s : estaciones->equipo.soldados) {
            cout << "        Soldado: " << s.nombre 
                 << " - Salud: " << s.salud 
                 << ", Arma: " << (s.mochila.arma ? s.mochila.arma->nombre : "Ninguna") 
                 << ", Defensa: " << (s.mochila.defensa ? s.mochila.defensa->nombre : "Ninguna") 
                 << ", Curacion: " << (s.mochila.curacion ? s.mochila.curacion->nombre : "Ninguna") << endl;
        }

        estaciones = estaciones->siguiente; // Avanzar al siguiente nodo
        i++;
    }
}


void asignarEquipoAEstacion(Estacion* estaciones, Equipo& equipo) {
    int estacionSeleccionada;
    mostrarEstacionesConS(estaciones);
    cout << "\nSeleccione la estacion donde desea anadir el equipo (ingrese el numero de la estacion): ";
    cin >> estacionSeleccionada;

    // Validar la seleccion de la estacion
    Estacion* temp = estaciones;
    int index = 0;
    while (temp != nullptr && index < estacionSeleccionada) {
        temp = temp->siguiente;
        index++;
    }

    // Comprobar si la estacion seleccionada es valida
    if (temp != nullptr) {
        // Asignar el equipo a la estacion seleccionada
        temp->equipo = equipo; // Asignar el equipo
        cout << "Equipo anadido a la estacion " << temp->nombreEstacion << "." << endl;

        // Aqui puedes agregar la logica para ingresar los soldados al equipo
        int numSoldados;
        cout << "¿Cuantos soldados desea agregar al equipo? ";
        cin >> numSoldados;

        for (int i = 0; i < numSoldados; i++) {
            string nombre;
            int salud;
            Mochila mochila; // Crear una nueva mochila para el soldado

            cout << "Ingrese el nombre del soldado " << (i + 1) << ": ";
            cin >> nombre;
            cout << "Ingrese la salud del soldado " << (i + 1) << ": ";
            cin >> salud;

            // Rellenar la mochila del soldado
            cout << "Rellenar mochila del soldado " << nombre << ":\n";
            seleccionarYAgregarArma(&mochila); // Seleccionar y agregar un arma
            seleccionarYAgregarDefensa(&mochila); // Seleccionar y agregar una defensa
            seleccionarYAgregarCuracion(&mochila); // Seleccionar y agregar una curacion

            // Crear el soldado con la mochila
            Soldado nuevoSoldado(nombre, salud, mochila);

            // Agregar el soldado al equipo
            temp->equipo.soldados.push_back(nuevoSoldado);

            // Mostrar la mochila del soldado
            cout << "Mochila del soldado " << nuevoSoldado.nombre << ":\n\n";
            mostrarMochila(mochila);
            cout << endl; // Linea en blanco entre soldados
        }
    } else {
        cout << "Estacion no valida." << endl;
    }
    system("pause");
}

void mostrarSoldados(Estacion* estaciones) {
    cout << "Soldados disponibles:\n";
    while (estaciones != nullptr) {
        cout << "\n* Estacion: " << estaciones->nombreEstacion << ":" <<endl<<endl;

        // Verificar si hay soldados en la estación
        if (estaciones->equipo.soldados.empty()) {
            cout << "   No hay soldados en esta estación." << endl;
        } else {
            int contador = 1;
            for (const auto& soldado : estaciones->equipo.soldados) {
                cout << "   " << contador++ << ". " << soldado.nombre 
                     << " (Salud: " << soldado.salud << ")\n"
                     << "       Arma: " << (soldado.mochila.arma ? soldado.mochila.arma->nombre : "Ninguna") << "\n"
                     << "       Defensa: " << (soldado.mochila.defensa ? soldado.mochila.defensa->nombre : "Ninguna") << "\n"
                     << "       Curacion: " << (soldado.mochila.curacion ? soldado.mochila.curacion->nombre : "Ninguna") << "\n";
            }
        }

        estaciones = estaciones->siguiente; // Avanzar a la siguiente estación
    }
}

Soldado* seleccionarSoldado(Estacion* estaciones) {
    mostrarSoldados(estaciones);
    int seleccion;
    cout << "Seleccione el numero del soldado que desea modificar: ";
    cin >> seleccion;cout<<endl;

    // Buscar el soldado en las estaciones
    int contador = 1;
    while (estaciones != nullptr) {
        for (auto& soldado : estaciones->equipo.soldados) {
            if (contador == seleccion) {
                return &soldado; // Retornar el puntero al soldado seleccionado
            }
            contador++;
        }
        estaciones = estaciones->siguiente; // Avanza a la siguiente estacion
    }

    cout << "Seleccion no valida.\n";
    return nullptr; // Retornar nullptr si no se encuentra el soldado
}


void modificarMochila(Soldado* soldado) {
    if (soldado == nullptr) {
        cout << "No se pudo modificar la mochila, soldado no valido.\n";
        return;
    }

    int opcion;
    do {
        cout << "\n-- Modificar Mochila de " << soldado->nombre << " --\n";
        cout << "1. Cambiar Arma\n";
        cout << "2. Cambiar Defensa\n";
        cout << "3. Cambiar Curacion\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Seleccionando nueva arma...\n";
                seleccionarYAgregarArma(&soldado->mochila);
                break;
            case 2:
                cout << "Seleccionando nueva defensa...\n";
                seleccionarYAgregarDefensa(&soldado->mochila);
                break;
            case 3:
                cout << "Seleccionando nueva curacion...\n";
                seleccionarYAgregarCuracion(&soldado->mochila);
                break;
            case 0:
                cout << "Volviendo al menu anterior...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 0);
}


int main(){

    Estacion* estaciones = nullptr;
    Estacion estacion;
    Equipo equipo;
    vector<Equipo> equiposExistentes;

    // Crear estaciones por defecto
    Estacion* nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Caracas";
    nuevaEstacion->numZombies = 3;
    nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Los Teques";
    nuevaEstacion->numZombies = 4;
    nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    nuevaEstacion->zombies.push_back(Zombie("Infectado por Hongos", 40, 50));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "La Guaira";
    nuevaEstacion->numZombies = 2;
    nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Maracay";
    nuevaEstacion->numZombies = 5;
    nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    nuevaEstacion->zombies.push_back(Zombie("Infectado por Hongos", 40, 50));
    nuevaEstacion->zombies.push_back(Zombie("Bioluminiscente", 60, 70));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Valencia";
    nuevaEstacion->numZombies = 3;
    nuevaEstacion->zombies.push_back(Zombie("Rapido y agil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    int opcion;

    Armas* armas[7];
    armas[0] = new Armas("Pistola", 1, "Arma de fuego", 1, 25, 15);
    armas[1] = new Armas("Fusil de Asalto", 2, "Arma de fuego", 1, 30, 30);
    armas[2] = new Armas("Coctel Molotov", 3, "Arma arrojadiza", 1, 60, 2);
    armas[3] = new Armas("Cuchillo", 4, "Arma blanca", 2, 15, 100);
    armas[4] = new Armas("Tuberia", 5, "Arma contundente", 2, 20, 60);
    armas[5] = new Armas("Liquido inflamable", 6, "Arma incendiaria", 2, 70, 1);
    armas[6] = new Armas("Trampa de caida", 7, "Trampa", 2, 90, 1);

    Defensa* defensas[4];
    defensas[0] = new Defensa("Chaleco antizombies", 50, 100);
    defensas[1] = new Defensa("Escudo", 30, 150);
    defensas[2] = new Defensa("Casco de moto", 20, 80);
    defensas[3] = new Defensa("Armadura pesada", 70, 200);

    Curacion* curaciones[4];
    curaciones[0] = new Curacion("Vendas", 20, 5);
    curaciones[1] = new Curacion("Botiquin", 50, 3);
    curaciones[2] = new Curacion("Antidoto experimental", 30, 2);
    curaciones[3] = new Curacion("Suero de supervivencia", 15, 10);

        do {
            system("cls"); // Limpia la consola
            cout << "\n-- Menu Proyecto 1: Running Dead --" << endl;
            cout << "1. Mostrar Accesorios predeterminados" << endl;
            cout << "2. Gestion Equipos" << endl;
            cout << "3. Gestion de Mochilas" << endl;
            cout << "4. Gestion de Estaciones y Zombies" << endl;
            cout << "5. Estatus de Mapa, Zombies y Soldados" << endl;
            cout << "6. Misiones" << endl;
            cout << "7. Bitacora" << endl;
            cout << "0. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1: {
                    int subOpcion;
                    do {
                        cout << "\n-- Gestion de Accesorios --" << endl;
                        cout << "1. Mostrar armas predeterminadas" << endl;
                        cout << "2. Mostrar defensas predeterminadas" << endl;
                        cout << "3. Mostrar curaciones predeterminadas" << endl;
                        cout << "0. Volver al menu" << endl;
                        cout << "Seleccione su opcion: ";
                        cin >> subOpcion;cout<<endl;

                        switch (subOpcion) {
                            case 1:
                                mostrarArmas(armas, 7);
                                break;
                            case 2:
                                mostrarDefensas(defensas, 4);
                                break;
                            case 3:
                                mostrarCuraciones(curaciones, 4);
                                break;
                            case 0:
                                break;
                            default:
                                cout << "Ingrese una opcion valida." << endl;
                                break;
                        }
                    } while (subOpcion != 0);
                    break;
                }
                case 2: {
                    int subOpcion2;
                    do {
                        cout << "\n-- Gestion de soldados y equipos --" << endl;
                        cout << "1. Ver estaciones y equipos" << endl;
                        cout << "2. Crear nuevo equipo" << endl;
                        cout << "0. Volver al menu principal" << endl;
                        cout << "Seleccione una opcion: ";
                        cin >> subOpcion2;

                        switch (subOpcion2) {
                            case 1:
                                mostrarEquiposPorEstacion(estaciones);
                                break;
                            case 2:
                                asignarEquipoAEstacion(estaciones, equipo);
                                break;
                            case 0:
                                cout << "Volviendo al menu principal..." << endl;
                                break;
                            default:
                                cout << "Opcion no valida. Intente de nuevo." << endl;
                                break;
                        }
                    } while (subOpcion2 != 0);
                    break;
                }
                case 3: {
                    int subOpcion3;
                    do {
                        cout << "\n-- Gestion de Mochila --" << endl;
                        cout << "1. Mostrar Mochilas y soldados" << endl;
                        cout << "2. Modificar contenido de la mochila" << endl;
                        cout << "0. Volver al menu principal" << endl;
                        cin >> subOpcion3;

                        switch (subOpcion3) {

                            case 1:
                                mostrarSoldados(estaciones);
                                break;
                            case 2:{
                                Soldado* soldado = seleccionarSoldado(estaciones);
                                modificarMochila(soldado);
                                break;
                                }
                            case 0:
                                cout << "Volviendo al menu principal..." << endl;
                                break;
                            default:
                                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                                break;
                        }
                    } while (subOpcion3 != 0);
                    break;
                }
                case 4: {
                    int subOpcion4;
                    do {
                        cout << "\n-- Gestion de Estaciones y Zombies --" << endl;
                        cout << "1. Crear estacion\n";
                        cout << "2. Mostrar estaciones\n";
                        cout << "3. Eliminar estacion\n";
                        cout << "0. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        cin >> subOpcion4;

                        switch (subOpcion4) {
                            case 1: 
                                crearEstacion(estaciones); 
                                break;
                            case 2: 
                                mostrarEstacionesConZ(estaciones); 
                                break;
                            case 3: {
                                int pos;
                                cout << "Ingrese la posicion de la estacion a eliminar: \n";
                                mostrarEstacionesConZ(estaciones);
                                cin >> pos;
                                eliminarEstacion(pos, estaciones);
                                break;
                            }
                            case 0:
                                break;
                            default: 
                                cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                                break;
                        }
                    } while (subOpcion4 != 0);
                    break;
                }
                case 5:
                    int subopcion5;
                    do{
                    cout<<endl<<endl<<"Estatus de Mapa, Zombies y Soldados";
                    cout<<endl<<"1. Mostrar Estaciones y Zombies";
                    cout<<endl<<"2. Mostrar Estaciones y soldados";
                    cout<<endl<<"3. Mostrar Estaciones, zombies y Soldados";
                    cout<<endl<<"0. Volver al menu principal";
                    cout<<"ingrese su opcion: ";cin>>subopcion5;
                    cout<<endl;

                    switch (subopcion5)
                    {
                    case 1:
                        mostrarEstacionesConZ(estaciones);
                        break;
                    case 2:
                        mostrarEstacionesConS(estaciones);
                        break;

                    case 3: 
                        mostrarEquiposPorEstacion(estaciones);
                        break;    

                    default:
                        cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                        break;
                    }
                    
                    } while (subopcion5 != 0);
                    
                    break;
                case 6:
                    // funciones para misiones
                    break;
                case 7:
                    // funciones para bitacora
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Ingrese una opcion valida." << endl;
                    break;
            }
        } while (opcion != 0); // Continua hasta que el usuario elija salir

        liberarEstaciones(estaciones);

        // Liberar memoria
        for (int i = 0; i < 7; i++) {
            delete armas[i];
        }

        for (int i = 0; i < 4; i++) {
            delete defensas[i];
        }

        for (int i = 0; i < 4; i++) {
            delete curaciones[i];
        }

        return 0;
    }
