// PROYECTO ZOMBIES REALIZADO POR CARSTENS, MATHIAS; LUCA, FRANCO.
// C.I. 31.046.461; 

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

// Gestión Accesorios: permite Agregar, Modificar, Eliminar accesorios, así como también buscar toda la información asociada a las mismos.
struct Armas {
    string nombre;
    int num_arma;
    string tipo_de_arma;
    int con_municion_o_cuerpo_cuerpo; // las que usan municion se toman como tipo 1, y si se usan una vez y ya se toman como tipo 2
    int dano;
    int municion;

    // Constructor para inicializar un zombie
    Armas(string n, int na, string tda, int cm_cc, int d, int m) 
        : nombre(n), num_arma(na), tipo_de_arma(tda), con_municion_o_cuerpo_cuerpo (cm_cc), dano(d),  municion(m) {}
};

struct Defensa{
    string nombre;
    int dano_defendido;
    int refuerzo;

    Defensa(string n, int d_d, int r) 
        : nombre(n), dano_defendido(d_d), refuerzo(r) {}
};

struct Curacion{
    string nombre;
    int vida_recuperada;
    int usos;

    Curacion(string n, int v_r, int u)
    : nombre(n), vida_recuperada(v_r), usos(u) {}
};

// Gestión Mochila:
struct Mochila {
    Armas* arma;      // Usar puntero para Armas
    Defensa* defensa; // Usar puntero para Defensa
    Curacion* curacion; // Usar puntero para Curación
    
    Mochila() : arma(nullptr), defensa(nullptr), curacion(nullptr) {}

    ~Mochila() {
        delete arma; // Liberar memoria al destruir la mochila
        delete defensa; // Liberar memoria al destruir la mochila
        delete curacion; // Liberar memoria al destruir la mochila
    }
};

// Función para agregar un arma a la mochila
void agregarArma(Mochila* mochila, Armas* armaSeleccionada) {
    if (mochila->arma == nullptr) { // Verificar si el campo arma está vacío
        mochila->arma = armaSeleccionada;
        cout << "Arma agregada: " << armaSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay un arma en la mochila. No se puede agregar: " << armaSeleccionada->nombre << endl;
    }
}

// Función para seleccionar un arma
Armas* seleccionarYAgregarArma(Mochila* mochila) {
    // Crear un array de punteros a Armas
    Armas* armas[7];
    armas[0] = new Armas("Pistola", 1, "Arma de fuego", 1, 25, 15);
    armas[1] = new Armas("Fusil de Asalto", 2, "Arma de fuego", 1, 30, 30);
    armas[2] = new Armas("Coctel Molotov", 3, "Arma arrojadiza", 1, 60, 2);
    armas[3] = new Armas("Cuchillo", 4, "Arma blanca", 2, 15, 100);
    armas[4] = new Armas("Tubería", 5, "Arma contundente", 2, 20, 60);
    armas[5] = new Armas("Líquido inflamable", 6, "Arma incendiaria", 2, 70, 1);
    armas[6] = new Armas("Trampa de caída", 7, "Trampa", 2, 90, 1);

    int opcion;
    cout << "Selecciona un arma:\n";
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << ". " << armas[i]->nombre << endl;
    }
    cout << "Elige una opción (1-7): ";
    cin >> opcion;

    // Validar la opción y agregar el arma a la mochila
    if (opcion >= 1 && opcion <= 7) {
        agregarArma(mochila, armas[opcion - 1]); // Agregar el arma seleccionada a la mochila
        return armas[opcion - 1]; // Retornar el puntero al arma seleccionada
    } else {
        cout << "Opción no válida" << endl;
        return nullptr; // Retornar nullptr si la opción no es válida
    }
}

// Función para mostrar las armas
void mostrarArmas(Armas* armas[], int cantidad) {
    cout << "Armas disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << armas[i]->nombre
             << ", Tipo: " << armas[i]->tipo_de_arma 
             << ", Daño: " << armas[i]->dano 
             << ", Munición: " << armas[i]->municion << ")\n";
    }
}


// Función para agregar una defensa a la mochila
void agregarDefensa(Mochila* mochila, Defensa* defensaSeleccionada) {
    if (mochila->defensa == nullptr) { // Verificar si el campo defensa está vacío
        mochila->defensa = defensaSeleccionada;
        cout << "Defensa agregada: " << defensaSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay una defensa en la mochila. No se puede agregar: " << defensaSeleccionada->nombre << endl;
    }
}

Defensa* seleccionarYAgregarDefensa(Mochila* mochila) {
    Defensa* defensas[4];
    defensas[0] = new Defensa("Chaleco antizombies", 50, 100);
    defensas[1] = new Defensa("Escudo", 30, 150);
    defensas[2] = new Defensa("Casco de moto", 20, 80);
    defensas[3] = new Defensa("Armadura pesada", 70, 200);

    int opcion;
    cout << "Selecciona una defensa:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << defensas[i]->nombre << endl;
    }
    cout << "Elige una opción (1-4): ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        agregarDefensa(mochila, defensas[opcion - 1]);
        return defensas[opcion - 1]; // Retornar el puntero a la defensa seleccionada
    } else {
        cout << "Opción no válida" << endl;
        return nullptr; // Retornar nullptr si la opción no es válida
    }
}

void mostrarDefensas(Defensa* defensas[], int cantidad) {
    cout << "Defensas disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << defensas[i]->nombre
            << ", Daño defendido: " << defensas[i]->dano_defendido 
            << ", Durabilidad: " << defensas[i]->refuerzo << endl;
    }
}

// Función para agregar una curación a la mochila
void agregarCuracion(Mochila* mochila, Curacion* curacionSeleccionada) {
    if (mochila->curacion == nullptr) { // Verificar si el campo curación está vacío
        mochila->curacion = curacionSeleccionada;
        cout << "Curación agregada: " << curacionSeleccionada->nombre << endl;
    } else {
        cout << "Ya hay una curación en la mochila. No se puede agregar: " << curacionSeleccionada->nombre << endl;
    }
}

Curacion* seleccionarYAgregarCuracion(Mochila* mochila) {
    Curacion* curaciones[4];
    curaciones[0] = new Curacion("Vendas", 20, 5);
    curaciones[1] = new Curacion("Botiquín", 50, 3);
    curaciones[2] = new Curacion("Antídoto experimental", 30, 2);
    curaciones[3] = new Curacion("Suero de supervivencia", 15, 10);

    int opcion;
    cout << "Selecciona una curación:\n";
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << curaciones[i]->nombre << endl;
    }
    cout << "Elige una opción (1-4): ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        agregarCuracion(mochila, curaciones[opcion - 1]); // Agregar la curación seleccionada a la mochila
        return curaciones[opcion - 1]; // Retornar el puntero a la curación seleccionada
    } else {
        cout << "Opción no válida" << endl;
        return nullptr; // Retornar nullptr si la opción no es válida
    }

    // Liberar memoria de las curaciones que no fueron seleccionadas
    for (int i = 0; i < 4; i++) {
        if (i != opcion - 1) {
            delete curaciones[i];
        }
    }
}

// Función para mostrar las curaciones disponibles
void mostrarCuraciones(Curacion* curaciones[], int cantidad) {
    cout << "Curaciones disponibles:\n";
    for (int i = 0; i < cantidad; i++) {
        cout << i + 1 << ". " << curaciones[i]->nombre
             << ", Vida recuperada: " << curaciones[i]->vida_recuperada 
             << ", Cantidad de usos: " << curaciones[i]->usos << endl;
    }
}

// Función para eliminar un arma
void eliminarArma(Mochila* mochila) {
    if (mochila->arma) {
        cout << "Eliminando arma: " << mochila->arma->nombre << endl;
        delete mochila->arma;
        mochila->arma = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay arma para eliminar.\n";
    }
}

// Función para eliminar una defensa
void eliminarDefensa(Mochila* mochila) {
    if (mochila->defensa) {
        cout << "Eliminando defensa: " << mochila->defensa->nombre << endl;
        delete mochila->defensa;
        mochila->defensa = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay defensa para eliminar.\n";
    }
}

// Función para eliminar una curación
void eliminarCuracion(Mochila* mochila) {
    if (mochila->curacion) {
        cout << "Eliminando curación: " << mochila->curacion->nombre << endl;
        delete mochila->curacion;
        mochila->curacion = nullptr; // Establecer el puntero a nullptr
    } else {
        cout << "No hay curación para eliminar.\n";
    }
}

void mostrarMochila(const Mochila& mochila) {
    if (mochila.arma != nullptr) {
        cout << "Arma: " << mochila.arma->nombre << endl;
        cout << "Número de arma: " << mochila.arma->num_arma << endl;
        cout << "Tipo de arma: " << mochila.arma->tipo_de_arma << endl;
        cout << "Con munición o cuerpo a cuerpo: " << mochila.arma->con_municion_o_cuerpo_cuerpo << endl;
        cout << "Daño: " << mochila.arma->dano << endl;
        cout << "Munición: " << mochila.arma->municion << endl;
    }

    if (mochila.defensa != nullptr) {
        cout << "Defensa: " << mochila.defensa->nombre << endl;
        cout << "Daño defendido: " << mochila.defensa->dano_defendido << endl;
        cout << "Refuerzo: " << mochila.defensa->refuerzo << endl;
    }

    if (mochila.curacion != nullptr) {
        cout << "Curación: " << mochila.curacion->nombre << endl;
        cout << "Vida recuperada: " << mochila.curacion->vida_recuperada << endl;
        cout << "Usos: " << mochila.curacion->usos << endl;
    }
}

void gestionarEliminacion(Mochila* mochila) {
    int opcion;
    mostrarMochila(*mochila);
    
    cout << "¿Qué deseas eliminar?\n";
    cout << "1. Arma\n";
    cout << "2. Defensa\n";
    cout << "3. Curación\n";
    cout << "Elige una opción (1-3): ";
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
            cout << "Opción no válida.\n";
            break;
    }
}

// Gestión de equipos:
struct Soldado {
    string nombre;
    int salud;
    Mochila mochila;

    // Constructor
    Soldado(string n, int s, Mochila m) 
    : nombre(n), salud(s), mochila(m) {}
};

struct Equipo {
    vector<Soldado> soldados; // Usar un vector para almacenar soldados

    // Agregar un soldado al equipo
    void agregarSoldado(const Soldado& soldado) {
        soldados.push_back(soldado);
    }

    // Mostrar todos los soldados en el equipo
    void mostrarEquipo() const {
        cout << "Equipo:\n";
        for (const auto& soldado : soldados) {
            cout << "Soldado: " << soldado.nombre << "\n";
            mostrarMochila(soldado.mochila);
            cout << "-------------------\n";
        }
    }
};

void crearSoldados(Armas* armas[], Defensa* defensas[], Curacion* curaciones[], Soldado& soldadoDebil, Soldado& soldadoMedio, Soldado& soldadoFuerte) {
    // Soldado débil
    Mochila mochilaDebil;
    mochilaDebil.arma = armas[0]; // Pistola
    mochilaDebil.defensa = defensas[0]; // Chaleco antizombies
    mochilaDebil.curacion = curaciones[0]; // Vendas
    soldadoDebil = Soldado("Soldado Débil", 50, mochilaDebil);

    // Soldado medio
    Mochila mochilaMedio;
    mochilaMedio.arma = armas[1]; // Fusil de Asalto
    mochilaMedio.defensa = defensas[1]; // Escudo
    mochilaMedio.curacion = curaciones[1]; // Botiquín
    soldadoMedio = Soldado("Soldado Medio", 75, mochilaMedio);

    // Soldado fuerte
    Mochila mochilaFuerte;
    mochilaFuerte.arma = armas[5]; // Líquido inflamable
    mochilaFuerte.defensa = defensas[3]; // Armadura pesada
    mochilaFuerte.curacion = curaciones[3]; // Suero de supervivencia
    soldadoFuerte = Soldado("Soldado Fuerte", 100, mochilaFuerte);
}

void modificarSoldado(Soldado& soldado, Armas* armas[], Defensa* defensas[], Curacion* curaciones[]) {
    int opcion;

    do {
        cout << "¿Qué deseas modificar para " << soldado.nombre << "?" << endl;
        cout << "1. Arma" << endl;
        cout << "2. Defensa" << endl;
        cout << "3. Curación" << endl;
        cout << "0. Salir" << endl;
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: { // Modificar arma
                cout << "Selecciona un nuevo arma para " << soldado.nombre << " (0 para cancelar):" << endl;
                for (int i = 0; i < 7; ++i) {
                    cout << i + 1 << ": " << armas[i];       
                    cout << i + 1 << ": " << armas[i]->nombre << endl;
                }
                cout << "Opción: ";
                cin >> opcion;
                if (opcion > 0 && opcion <= 7) {
                    soldado.mochila.arma = armas[opcion - 1]; // Actualizar el arma
                    cout << "Arma actualizada a: " << soldado.mochila.arma->nombre << endl;
                } else if (opcion != 0) {
                    cout << "Opción no válida. El arma no ha sido modificada." << endl;
                }
                break;
            }
            case 2: { // Modificar defensa
                cout << "Selecciona una nueva defensa para " << soldado.nombre << " (0 para cancelar):" << endl;
                for (int i = 0; i < 4; ++i) {
                    cout << i + 1 << ": " << defensas[i]->nombre << endl;
                }
                cout << "Opción: ";
                cin >> opcion;
                if (opcion > 0 && opcion <= 4) {
                    soldado.mochila.defensa = defensas[opcion - 1]; // Actualizar la defensa
                    cout << "Defensa actualizada a: " << soldado.mochila.defensa->nombre << endl;
                } else if (opcion != 0) {
                    cout << "Opción no válida. La defensa no ha sido modificada." << endl;
                }
                break;
            }
            case 3: { // Modificar curación
                cout << "Selecciona un nuevo ítem de curación para " << soldado.nombre << " (0 para cancelar):" << endl;
                for (int i = 0; i < 4; ++i) {
                    cout << i + 1 << ": " << curaciones[i]->nombre << endl;
                }
                cout << "Opción: ";
                cin >> opcion;
                if (opcion > 0 && opcion <= 4) {
                    soldado.mochila.curacion = curaciones[opcion - 1]; // Actualizar la curación
                    cout << "Ítem de curación actualizado a: " << soldado.mochila.curacion->nombre << endl;
                } else if (opcion != 0) {
                    cout << "Opción no válida. El ítem de curación no ha sido modificado." << endl;
                }
                break;
            }
            case 0:
                cout << "Saliendo de la modificación." << endl;
                break;
            default:
                cout << "Opción no válida. Intenta de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
}

// Estructura para representar una Estacion
struct Estacion {
    string nombreEstacion;
    int numZombies;
    vector<Zombie> zombies;
    struct Equipo equipo;
    Estacion* siguiente;
};

// Funcion para verificar si la lista de estaciones esta vacia
bool estaVacio(Estacion* lista) {
    return lista == nullptr;
}

// Funcion para mostrar las estaciones
void mostrarEstaciones(Estacion* estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista esta vacia." << endl;
        return;
    }

    int i = 0;
    while (estaciones != nullptr) {
        cout << i << ". " << estaciones->nombreEstacion<<endl<<endl;
        cout << "    () Numero de zombies: " << estaciones->numZombies<<endl;
        for (const Zombie& z : estaciones->zombies) {
            cout << "        " << z.nombre << " - Fortaleza: " << z.fortaleza << ", Ataque: " << z.ataque<<endl;
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

    for (int i = 0; i < nuevaEstacion->numZombies; i++) {
        int tipo;
        cout << "Zombie numero " << i + 1 << " - Seleccione el tipo de zombie:\n";
        cout << "1. Rápido y Ágil\n";
        cout << "2. Tanque\n";
        cout << "3. Inteligente\n";
        cout << "4. Infectado por Hongos\n";
        cout << "5. Bioluminiscente\n";
        cout << "Ingrese el numero del tipo de zombie que desea agregar: ";
        cin >> tipo;

        // Validar tipo de zombie
        if (tipo < 1 || tipo > 5) {
            cout << "Tipo de zombie desconocido. Por favor, intente de nuevo.\n";
            i--; // Decrementar i para volver a preguntar
            continue;
        }

        // Crear el zombie y agregarlo al vector de la estacion
        switch (tipo) {
            case 1: nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80)); break;
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
        mostrarEstaciones(estaciones);
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

void modificarDatosSoldado(Soldado& soldado) {
    string nuevoNombre;
    int nuevaSalud;

    cout << "Modificar datos del soldado " << soldado.nombre << endl;

    cout << "Ingrese el nuevo nombre del soldado (deje en blanco para no modificar): ";
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, nuevoNombre); // Permitir nombres con espacios

    if (!nuevoNombre.empty()) {
        soldado.nombre = nuevoNombre; // Solo se modifica si se ingresó un nuevo nombre
    }

    do {
        cout << "Ingrese la nueva salud del soldado (actual: " << soldado.salud << "): ";
        cin >> nuevaSalud;

        if (nuevaSalud > 100 || nuevaSalud < 0) {
            cout << "La salud del soldado debe ser mayor a 0 y menor a 100.\n";
        }
    } while (nuevaSalud > 100 || nuevaSalud < 0);

    soldado.salud = nuevaSalud; // Actualizar la salud del soldado
    cout << "Datos del soldado actualizados." << endl;
}

void mostrarEquiposPorEstacion(Estacion* estaciones) {
    if (estaVacio(estaciones)) {
        cout << "La lista está vacía." << endl;
        return;
    }

    int i = 0;
    while (estaciones != nullptr) {
        cout << "Estación: " << estaciones->nombreEstacion << endl;
        cout << "Número de Zombies: " << estaciones->numZombies << endl;

        // Mostrar soldados en el equipo de la estación
        cout << "Soldados en esta estación: " << endl;
        for (const Soldado& s : estaciones->equipo.soldados) {
            cout << "        Soldado: " << s.nombre 
                 << " - Salud: " << s.salud 
                 << ", Arma: " << s.mochila.arma 
                 << ", Defensa: " << s.mochila.defensa 
                 << ", Curación: " << s.mochila.curacion << endl;
        }

        estaciones = estaciones->siguiente; // Avanzar al siguiente nodo
        i++;
    }
}

/*
void eliminarSoldado(Equipo& equipo, Soldado& soldado) {
    // Verificar si la salud del soldado es menor o igual a 0
    if (soldado.salud <= 0) {
        // Eliminar el soldado del equipo
        equipo.eliminarSoldado(soldado); // Asumiendo que hay un método para eliminar soldados en el equipo
        cout << "Soldado " << soldado.nombre << " ha sido eliminado debido a que su salud es " << soldado.salud << "." << endl;
    } else {
        cout << "No se puede eliminar al soldado " << soldado.nombre << " porque su salud es " << soldado.salud << "." << endl;
    }
}
*/
int main() {

    Estacion* estaciones = nullptr;
    Estacion estacion;
    Equipo equipo;

    // Crear estaciones por defecto
    Estacion* nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Caracas";
    nuevaEstacion->numZombies = 3;
    nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Los Teques";
    nuevaEstacion->numZombies = 4;
    nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    nuevaEstacion->zombies.push_back(Zombie("Infectado por Hongos", 40, 50));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "La Guaira";
    nuevaEstacion->numZombies = 2;
    nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Maracay";
    nuevaEstacion->numZombies = 5;
    nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80));
    nuevaEstacion->zombies.push_back(Zombie("Tanque", 100, 30));
    nuevaEstacion->zombies.push_back(Zombie("Inteligente", 70, 60));
    nuevaEstacion->zombies.push_back(Zombie("Infectado por Hongos", 40, 50));
    nuevaEstacion->zombies.push_back(Zombie("Bioluminiscente", 60, 70));
    nuevaEstacion->siguiente = estaciones;
    estaciones = nuevaEstacion;

    nuevaEstacion = new Estacion();
    nuevaEstacion->nombreEstacion = "Valencia";
    nuevaEstacion->numZombies = 3;
    nuevaEstacion->zombies.push_back(Zombie("Rápido y Ágil", 50, 80));
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
    armas[4] = new Armas("Tubería", 5, "Arma contundente", 2, 20, 60);
    armas[5] = new Armas("Líquido inflamable", 6, "Arma incendiaria", 2, 70, 1);
    armas[6] = new Armas("Trampa de caída", 7, "Trampa", 2, 90, 1);

    Defensa* defensas[4];
    defensas[0] = new Defensa("Chaleco antizombies", 50, 100);
    defensas[1] = new Defensa("Escudo", 30, 150);
    defensas[2] = new Defensa("Casco de moto", 20, 80);
    defensas[3] = new Defensa("Armadura pesada", 70, 200);

    Curacion* curaciones[4];
    curaciones[0] = new Curacion("Vendas", 20, 5);
    curaciones[1] = new Curacion("Botiquín", 50, 3);
    curaciones[2] = new Curacion("Antídoto experimental", 30, 2);
    curaciones[3] = new Curacion("Suero de supervivencia", 15, 10);

    do {
        system("cls");
        cout << "\n-- Menú Proyecto 1: Running Dead --" << endl;
        cout << "1. Gestión Accesorios" << endl;
        cout << "2. Gestión Equipos" << endl;
        cout << "3. Gestión de Mochilas" << endl;
        cout << "4. Gestion de Estaciones y Zombies" << endl;
        cout << "5. Misiones" << endl;
        cout << "6. Bitácora" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {

            case 1: {
                int subOpcion;
                do {
                    cout << "\n-- Gestión de Accesorios --" << endl;
                    cout << "1. Mostrar armas predeterminadas" << endl;
                    cout << "2. Mostrar artículos de defensa predeterminados" << endl;
                    cout << "3. Mostrar artículos de curación predeterminados" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> subOpcion;

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
                        default:
                            cout << "Ingrese una opción válida." << endl;
                            break;
                    }
                } while (subOpcion < 1 || subOpcion > 3);
                break;
            }
            case 2:
        cout << "\n-- Gestión de soldados y equipos --" << endl;
        do {
            cout << "1. Agregar soldados a un equipo" << endl;
            cout << "2. Modificar soldados de un equipo" << endl;
            cout << "3. Eliminar soldados de un equipo" << endl;
            cout << "4. Mostrar equipos con sus miembros" << endl;
            cout << "0. Salir" << endl; // Opción para salir del menú
            cout << "Seleccione una opción: ";
            cin >> opcion;
            cout << endl;

            switch(opcion) {
                case 1:
                    break;
                case 2:
                    // Llama a la función para modificar soldados
                    break;
                case 3:
                    // Llama a la función para eliminar soldados
                    break;
                case 4:
                    mostrarEquiposPorEstacion(estaciones);// Llama a la función para mostrar equipos
                    break;
                case 0:
                    cout << "Saliendo del menú de gestión de soldados y equipos." << endl;
                    break;
                default:
                    cout << "Opción no válida. Por favor, seleccione una opción válida." << endl;
                    break;
            }
            cout << endl;
        } while (opcion != 0); // Repite hasta que el usuario elija salir
        break;
            case 3:
                cout << "\n -- Gestión de mochila --" << endl;
                do {
                    cout << "1. Modificar items de la mochila" << endl;
                    cout << "2. Mostrar items de la mochila" << endl;
                    cout << "0. Salir" << endl; // Opción para salir del menú
                    cout << "Seleccione una opción: ";
                    cin >> opcion;
                    cout << endl;
                    switch(opcion) {
                        case 1: ; break;
                        case 2: ; break;
                        case 0: ; break;
                            default: cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                        }
                    } while (opcion != 0);
                break;
            case 4:
                cout << "\n-- Gestion de Estaciones y Zombies --" << endl;
                do {
                    cout << "1. Crear estacion\n";
                    cout << "2. Mostrar estaciones\n";
                    cout << "3. Eliminar estacion\n";
                    cout << "0. Salir\n";
                    cout << "Ingrese su opcion: ";
                    cin >> opcion;cout<<endl;

                    switch (opcion) {
                        case 1: crearEstacion(estaciones); break;
                        case 2: mostrarEstaciones(estaciones); break;
                        case 3: {
                            int pos;
                            cout << "Ingrese la posicion de la estacion a eliminar: \n";
                            mostrarEstaciones(estaciones);
                            cin >> pos;
                            eliminarEstacion(pos, estaciones);
                            break;
                            }
                            case 4: break;
                            default: cout << "Opcion no valida. Por favor, intente de nuevo.\n";
                        }
                    } while (opcion != 0);

                    break;
                break;
            case 5:
                // funciones para misiones
                break;
            case 6:
                // funciones para bitácora
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Ingrese una opción válida." << endl;
                break;
        }
    } while (opcion != 0); // Continúa hasta que el usuario elija salir

    liberarEstaciones(estaciones);

    return 0;
}