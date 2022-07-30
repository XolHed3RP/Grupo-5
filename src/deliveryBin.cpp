#include "../lib/global.h"

using namespace std;
struct provincia
{
    unsigned int Id = 0;
    char sNombre[50];
    int iPoblacion;
    float fTemperatura;
    char lstPlatoTipico[100];
};
vector<provincia> lstProvincia;
const string pathfilebinary = "../resorce/database/delivery.dat";
unsigned int START_ID = 1;
bool leerArchivoBinario();
void escribirArchivoBinario();
void eliminarProvincia();
void presentarProvincias();
void presentarProvincia();
void presentarProvincia(provincia p);
void agregarProvincia();
void listarProvincias();
bool existRepetido(string elemento);
void buscarProvinciaAv();
int menu();
void Creditos();
string tolowerStr(string str);
void segmentarCadena(const string str, const char delim, vector<string> &lst);
bool busquedaBin();
void Id();
int main()
{
    leerArchivoBinario();
    do
    {
        switch (menu())
        {
        case AGREGAR:
            agregarProvincia();
            break;
        case PRESENTAR:
            presentarProvincias();
            break;
        case BUSCARPRO:
            presentarProvincia();
            break;
        case BUSCARPROAVANZADO:
            buscarProvinciaAv();
            break;
        case GUARDAR:
            escribirArchivoBinario();
            break;
        case ELIMINAR:
            eliminarProvincia();
            break;
        case SALIR:
            Colors(BLACK, CYAN);
            cout << endl
                 << "Regrese pronto..." << endl;
            exit(0);
        case ABOUT:
            Creditos();
            break;
        case BUSCARBIN:
            busquedaBin();
            break;
        default:
            Colors(BLACK, CYAN);
            cout << endl
                 << "Seleccion no valida" << endl;
            break;
        }
    } while (true);
}

bool leerArchivoBinario()
{
    ifstream rf(pathfilebinary, ios::in | ios::binary);
    Colors(MAGENTA, BLACK);
    cout << endl
         << "\nAbrir archivo:" << pathfilebinary << endl
         << endl;
    if (!rf)
    {
        Colors(RED, BLACK);
        cout << endl
             << " << error >>" << endl;
        return false;
    }
    provincia tp[1];
    while (rf.read((char *)&tp[0], sizeof(provincia)))
        lstProvincia.push_back(tp[0]);
    rf.close();
    return true;
}
void escribirArchivoBinario()
{
    ofstream f(pathfilebinary, ios::out | ios_base::binary);
    Colors(MAGENTA, BLACK);
    cout << endl
         << "Escribir archivo: " << pathfilebinary << endl
         << endl;
    if (f.good())
    {
        for (auto &&prov : lstProvincia)
            f.write((char *)&prov, sizeof(provincia));
    }
    f.close();
}

void agregarProvincia() // falta id
{
    string str = "s";
    string strIn2;
    do
    {

        struct provincia prov;
        Colors(GREEN, BLACK);
        cout << endl
             << "------ Ingresar datos de provincia  ------ " << endl
             << endl;
        prov.Id = lstProvincia.size() + 1;

        Colors(BLACK, BROWN);
        cout << "<+> Nombre: ";

        Colors(BLACK, BLACK);
        cin.getline(prov.sNombre, sizeof(prov.sNombre));

        if (existRepetido(prov.sNombre))
            break;

        Colors(BLACK, BLUE);
        cout << "<+> Poblacion: ";

        Colors(BLACK, BLACK);
        cin >> prov.iPoblacion;
        cin.clear();
        fflush(stdin);

        Colors(BLACK, MAGENTA);
        cout << "<+> Temperatura: ";

        Colors(BLACK, BLACK);
        cin >> prov.fTemperatura;
        cin.clear();
        fflush(stdin);

        Colors(BLACK, GREEN);
        cout << "<+> PlatoTipico (separados por coma): ";

        Colors(BLACK, BLACK);
        getline(cin, strIn2);
        strcpy(prov.lstPlatoTipico, strIn2.c_str());
        cin.clear();
        fflush(stdin);

        Colors(BLACK, RED);
        cout << "Deseas salir (s): ";

        Colors(BLACK, BLACK);
        getline(cin, str);
        cin.clear();
        fflush(stdin);

        if (!existRepetido(prov.sNombre))
            lstProvincia.push_back(prov);

    } while (str != "s");
    Id();
}

void presentarProvincia()
{
    Colors(GREEN, BLACK);
    cout << endl
         << "------ Buscar Provincia -------" << endl
         << endl;
    bool encondrado = false;
    string prov = "";
    Colors(BLACK, BROWN);
    cout << "Ingresa el Nombre de la provincia: ";
    getline(cin, prov);

    for (auto &&provincia : lstProvincia)
    {
        if (tolowerStr(provincia.sNombre) == tolowerStr(prov))
        {
            presentarProvincia(provincia);
            encondrado = true;
        }
    }
    if (!encondrado)
    {
        Colors(BLACK, RED);
        cout << endl
             << "No se encontro la provincia " << prov << endl;
    }
}

void eliminarProvincia()
{
    string prov = "";
    int indexProv = 0;
    bool encontrado = false;

    Colors(GREEN, BLACK);
    cout << endl
         << "-------- Eliminar Provincia --------" << endl;

    listarProvincias();

    Colors(BLACK, BROWN);
    cout << endl
         << "Ingrese el nombre de la provincia por eliminar : ";
    Colors(BLACK, BLACK);
    getline(cin, prov);

    for (auto &&provincia : lstProvincia)
    {
        if (tolowerStr(provincia.sNombre) == tolowerStr(prov))
        {
            string opcion = "x";

            presentarProvincia(provincia);

            Colors(BLACK, GREEN);
            cout << "Presione (x) para confirmar: ";

            Colors(BLACK, BLUE);
            cout << endl
                 << "<-> ";
            Colors(BLACK, BLACK);
            cin >>
                opcion;
            cin.clear();

            if (opcion == "x")
            {
                Colors(BLACK, RED);
                cout << endl
                     << "Se elimino correctamente..." << endl;
                lstProvincia.erase(lstProvincia.begin() + indexProv);
                Id();
                encontrado = true;
                break;
            }
        }
        indexProv++;
    }
    if (!encontrado)
    {
        Colors(BLACK, RED);
        cout << endl
             << "No se encontro la provincia " << prov << endl;
    }
}
void listarProvincias()
{
    Colors(BLACK, BROWN);
    cout << endl
         << "Provincias registradas:" << endl
         << endl;
    for (auto &&prov : lstProvincia)
    {
        Colors(BLACK, CYAN);
        cout << prov.Id;
        Colors(BLACK, GREEN);
        cout << ends << prov.sNombre << endl;
    }
}

void presentarProvincia(provincia p)
{
    Colors(BLACK, BLACK);
    cout << endl
         << "__________________________________" << endl
         << endl;

    Colors(BLACK, RED);
    cout << "Provincia  # ";
    Colors(BLACK, BLACK);
    cout << p.Id << endl;

    Colors(BLACK, BROWN);
    cout << "Nombre: ";
    Colors(BLACK, BLACK);
    cout << p.sNombre << endl;

    Colors(BLACK, BLUE);
    cout << "Poblacion: ";
    Colors(BLACK, BLACK);
    cout << p.iPoblacion << endl;

    Colors(BLACK, MAGENTA);
    cout << "Temperatura: ";
    Colors(BLACK, BLACK);
    cout << p.fTemperatura << endl;

    Colors(BLACK, GREEN);
    cout << "Platos-Tipicos: ";
    Colors(BLACK, BLACK);
    cout << p.lstPlatoTipico << endl;

    vector<string> lstPlatoTipico;
    segmentarCadena(p.lstPlatoTipico, ',', lstPlatoTipico);
    for (const auto &pt : lstPlatoTipico)
        cout << "\t" << pt << endl;

    cout << endl
         << "__________________________________" << endl
         << endl;
}
void presentarProvincias()
{
    Colors(GREEN, BLACK);
    cout
        << endl
        << "-------    Provincias   ----------" << endl;
    for (auto &&prov : lstProvincia)
        presentarProvincia(prov);
}

int menu()
{
    int eleccion;
    do
    {
        Colors(BLUE, BLACK);
        cout << endl
             << "()---Provincias del Ecuador---()\n";
        Colors(BLACK, GREEN);
        cout << endl
             << "Ingrese una opcion: \n"
             << endl
             << AGREGAR << " | Agregar provincias        |" << endl
             << PRESENTAR << " | Presentar provincias      |" << endl
             << BUSCARPRO << " | Buscar provincia          |" << endl
             << BUSCARPROAVANZADO << " | Buscar provincia avanzado |" << endl
             << GUARDAR << " | Guardar provincias        | " << endl
             << ELIMINAR << " | Eliminar Provincias       | " << endl
             << ABOUT << " | Creditos                  |" << endl
             << BUSCARBIN << " | Buscar bin                |" << endl
             << SALIR << " | Salir del sistema         | " << endl;
        Colors(BLACK, BROWN);
        cout
            << "\nSu seleccion: ";
        Colors(BLACK, BLACK);
        cin >>
            eleccion;
        cin.clear();
        fflush(stdin);
    } while (eleccion < 0 || eleccion > 8);
    return eleccion;
}

string tolowerStr(string str)
{
    for (int x = 0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}
void segmentarCadena(const string str, const char delim, vector<string> &outlst)
{
    string strDiv;
    stringstream s(str);
    while (getline(s, strDiv, delim))
        outlst.push_back(strDiv);
}

void buscarProvinciaAv()
{
    bool encontrado = false, aceptado = true;
    int count;
    char confirmacion;
    string entrada;
    Colors(GREEN, BLACK);
    cout
        << endl
        << "------- Provincias avanzado  ----------" << endl;
    Colors(BLACK, BROWN);
    cout << endl
         << "Ingrese la provincia a presentar: ";
    Colors(BLACK, BLACK);
    getline(cin, entrada);
    cin.clear();
    for (auto &&i : lstProvincia)
    {
        count = 0;
        string lower = tolowerStr(i.sNombre);
        string lecturadeentrada = tolowerStr(entrada);
        for (int x = 0; x <= lecturadeentrada.length(); x++)
        {
            if (lower[x] == lecturadeentrada[x] && lecturadeentrada[x] != ' ')
                count++;
            if (count >= 3)
            {
                Colors(BLACK, BLUE);
                cout << endl
                     << " ¿Usted busca " << i.sNombre << "?, Seleccione (S/N) " << endl;
                Colors(BLACK, RED);
                cout
                    << "<+>: ";
                Colors(BLACK, BLACK);
                cin >> confirmacion;
                cin.clear();
                if (confirmacion == 'S' || confirmacion == 's')
                {
                    presentarProvincia(i);
                    encontrado = true;
                    break;
                }
                else if (confirmacion == 'N' || confirmacion == 'n')
                {
                    break;
                }
                if (confirmacion != 'S' || confirmacion != 's' || confirmacion != 'N' || confirmacion != 'n')
                {
                    Colors(BLACK, RED);
                    cout << endl
                         << "Ingreso no valido, intentelo de nuevo" << endl
                         << endl;
                }
            }
        }
    }
    if (!encontrado)
    {
        Colors(BLACK, RED);
        cout << endl
             << " No se han encontrado similitudes" << endl
             << endl;
    }
}

void Creditos()
{
    Colors(GREEN, BLACK);
    cout << endl
         << endl
         << "------ Integrantes ------ " << endl
         << endl;
    Colors(BLACK, BLUE);
    cout << " |            Correo              |" << ends
         << " |        Nombre        |" << endl
         << " |________________________________|" << ends
         << " |______________________|" << endl;
    cout << " | ariel.amaguana@epn.edu.ec      |" << ends
         << " | Ariel Amaguaña       |" << endl
         << " | luis.rocha@epn.edu.ec          |" << ends
         << " | Luis Rocha           |" << endl
         << " | johan.bano@epn.edu.ec          |" << ends
         << " | Johan Bano           |" << endl
         << " | erick.ballas@epn.edu.ec        |" << ends
         << " | Erick Ballas         |" << endl
         << " | gianfranco.pupiales@epn.edu.ec |" << ends
         << " | Gianfranco Pupiales  |" << endl
         << endl;
}

bool busquedaBin()
{
    ifstream rf(pathfilebinary, ios::in | ios::binary);
    Colors(MAGENTA, BLACK);
    cout << endl
         << "\nAbrir archivo:" << pathfilebinary << endl
         << endl;
    if (!rf)
    {
        Colors(RED, BLACK);
        cout << endl
             << " << error >>" << endl;
        return false;
    }
    Colors(GREEN, BLACK);
    cout << endl
         << "------ Posicion de la provincia -------" << endl;
    int n;
    Colors(BLACK, BROWN);
    cout << endl
         << "Indique el # de provincia: ";
    Colors(BLACK, BLACK);
    cin >> n;
    rf.seekg((n - 1) * sizeof(provincia));
    provincia tp[1];
    rf.read((char *)&tp[0], sizeof(provincia));
    presentarProvincia(tp[0]);

    rf.close();
    return true;
}

void Id()
{
    for (auto &&prov : lstProvincia)
    {
        prov.Id = START_ID;
        START_ID++;
    }
}
bool existRepetido(string elemento)
{
    bool ban = false;
    for (auto &&prov : lstProvincia)
        if (prov.sNombre == elemento)
        {
            Colors(BLACK, RED);
            cout << endl
                 << "La provincia " << elemento << " ya existe" << endl;
            ban = true;
            continue;
        }
    return ban;
}
// Nice :D
/*
TAREA: deliberyBin
- 0.5 por item resuelto
- Equipos de 5 o 6 personas

 | Agregar provincias      |   << arreglar, evitar repetidos, Agregar a la estructura unsigned int Id (autoincremental)
 | Presentar provincias    |   << listar todas las provincias
 | Buscar provincia        |   << pedir nombre de provincia ... buscar y presentar : LOja
 | Buscar Avanzada         |   << pedir nombre de provincia ... buscar y presentar las que coindidan : loxa, --> loja
 | Guardar provincias      |
 | Eliminar provincias     |
0| Salir del sistema      |

>> captuas de pantalla del trabajo colaborativo
<< investigar como recupera directamente del archivo la estructura de datos >>
>> agregar color 0,1
*/