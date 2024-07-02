// надо заменить все long long и unsigned long long на библиотеку GMP
#include <QCoreApplication>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <gmpxx.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#include "dialog.h"
//#include "ui_dialog.h"
//###########################################################################
#include <QDataStream>
#include <QDebug>
#include <QFile>

#include <QFileDialog>

#include <QProcess>
#include <fstream>
#include <iostream>

#include <QApplication>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//###########################################################################
// переменные:
bool Odin_Uchitelia;
bool Odin_Programmi;
int var;
int neuron_index = 0, synapse_index = 0;

constexpr size_t NUM_SYNAPSES = 10105;

constexpr size_t NUM_NEYRONS = 205 ;
std::vector<mpz_class> list_of_neurons(NUM_NEYRONS);
std::vector<mpz_class> list_of_synapses(NUM_SYNAPSES);
//const mpz_class MAX_VALUE("18446744073709551615");
const std::string FILE_PATH = "/home/viktor/my_projects_qt_2/sgenerirovaty_sinapsi/random_sinapsi.bin";
//##################################################################

//###########################################################################

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция для чтения чисел-синапсов из бинарного файла

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readFromFile(std::vector<mpz_class>& list_of_synapses, const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        qCritical() << "Ошибка открытия файла для чтения";
        return;
    }

    for (size_t i = 0; i < NUM_SYNAPSES; ++i) {
        size_t size;
        inFile.read(reinterpret_cast<char*>(&size), sizeof(size));
        std::vector<char> buffer(size);
        inFile.read(buffer.data(), size);
        list_of_synapses[i].set_str(std::string(buffer.begin(), buffer.end()), 10);
    }

    inFile.close();
}

void printVector(const std::vector<mpz_class>& list_of_synapses) {
    int i=0;
    for (const auto& value : list_of_synapses) {
        qDebug() <<i<< ":"<< QString::fromStdString(value.get_str());
        i++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//########################################################################
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
mpz_class activationFunction( // long long list_of_neurons.at(var)
    int var
    //  ,
    //   int b
    )
{
  //  mpz_class base, exponent, result;

    mpz_class giperparametr =2;//0;//2;//200;
   // base=3; /// тут скорее 3 потому что 2,7
   // exponent = list_of_neurons.at(var); // степень
   // result = pow(base, exponent);
    // Инициализация больших целых чисел
    mpz_class base("3");
    mpz_class exp(list_of_neurons.at(var));
    mpz_class mod("4611686018000000000");
    mpz_class result;
    // Вычисление (base ^ exp) % mod
    mpz_powm(result.get_mpz_t(), base.get_mpz_t(), exp.get_mpz_t(), mod.get_mpz_t());
   // mpz_powm ( result,  3,  exponent, 4611686018000000000);
    if (list_of_neurons.at(var) <= 0)
        list_of_neurons.at(var) =list_of_neurons.at(var) * giperparametr * (result - 1);
    return (  list_of_neurons.at(var));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//const QString RANDOM_NUMBERS_FILE_NAME = "random_numbers.bin";

std::vector<mpz_class> readRandomNumbersFromFile(const QString& fileName) {
    std::vector<mpz_class> numbers;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to open random numbers file" << std::endl;
        return numbers;
    }
    QDataStream in(&file);
    while (!in.atEnd() && numbers.size() < 205) {
        QByteArray byteArray;
        in >> byteArray;
        numbers.push_back(mpz_class(byteArray.constData()));
    }
    file.close();
    return numbers;
}

void printVector2(const std::vector<mpz_class>& vec) {
    for (const auto& number : vec) {
        std::cout << number.get_str() << std::endl;
    }
}



// конец объявлений функций
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
 //   QCoreApplication a(argc, argv);

    // Используем QApplication вместо QCoreApplication, чтобы поддерживать графические компоненты
    QApplication app(argc, argv);
//########################################################################################################
    std::cout << "Funktsiya_Resheniya_6" << std::endl;
//########################################################################################################
// читаем синапсы из файла в вектор
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*

//    std::vector<mpz_class> read_synapses(NUM_SYNAPSES);
  readFromFile(list_of_synapses
        //read_synapses
                 , FILE_PATH);

  qDebug() << "Размер list_of_synapses:" << list_of_synapses.size();
    std::cout << "конец чтения синапсов в вектор" << std::endl;

  // Вывод значений вектора в консоль
 printVector(list_of_synapses
       // read_synapses
                );
  //   printVector(list_of_synapses);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "//"
                 "#################################################################################"
                 "#######################"
              << std::endl;
    //###########################################################################
//////////////////// считали синапсы в вектор //////////////////////////////////////////////////////////////////////
    // читаем нейроны в вектор

    // Вызов диалога выбора файла
    QString fileName_neyroni = QFileDialog::getOpenFileName(nullptr, "Выберите файл",
                                                            //"/home/viktor/1_rukoy/"
                                                            "/home/viktor/1_rukoy/scale/combined_numbers/"
                                                            ,  "bin Files (*.bin)");

    // Проверка, был ли файл выбран
    if (!fileName_neyroni.isEmpty()) {
        qDebug() << "Выбранный файл:" << fileName_neyroni;
    } else {
        qDebug() << "Файл не был выбран.";
    }
    // Преобразование QString в std::string
    std::string stdFileName_neyroni = fileName_neyroni.toStdString();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// читаем нейроны из файла в вектор
    // Чтение файла с 205 случайными числами и преобразование в вектор mpz_class
 //   std::vector<mpz_class>
        list_of_neurons = readRandomNumbersFromFile(
      //  RANDOM_NUMBERS_FILE_NAME
        fileName_neyroni
                                                                    );
    // Вывод вектора в консоль
    printVector2(//randomVector
          list_of_neurons       );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*


         qDebug() << "Размер list_of_neurons:" << list_of_neurons.size();
         std::cout << "конец чтения нейронов в вектор" << std::endl;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     // Проверка содержимого вектора

//###########################################################################
////////////////////////// считали нейроны в вектор ////////////////////////////////////////////////////////////////



    return app.exec();
}
