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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//###########################################################################
// переменные:
bool Odin_Uchitelia;
bool Odin_Programmi;
int var;
int neuron_index = 0, synapse_index = 0;
std::vector<mpz_class> list_of_neurons;
std::vector<mpz_class> list_of_synapses;
//##################################################################
//######################## 5 ##################################################
// Функция для чтения 205 long long чисел из бинарного файла
std::vector<mpz_class> read205LongLongFromBinaryFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Ошибка открытия бинарного файла.");
    }

    std::vector<mpz_class> list_of_neurons(205);
    file.read(reinterpret_cast<char *>(list_of_neurons.data()), 205 * sizeof(mpz_class));

    if (file.gcount() != 205 * sizeof(mpz_class)) {
        throw std::runtime_error("Недостаточно данных в бинарном файле.");
    }

    return list_of_neurons;
}
//###########################################################################
//############################# 8 ##############################################
// Функция для чтения mpz_class из QDataStream
void readMpzFromStream(QDataStream &in, mpz_class &number) {
    QByteArray byteArray;
    in >> byteArray;

    // Инициализация mpz_class из массива байтов
    number.set_str(byteArray.toStdString(), 10);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Функция для чтения чисел из бинарного файла
std::vector<mpz_class> readNumbersFromFile2(const QString &fileName, size_t count)
{
    std::vector<mpz_class> list_of_synapses;
    list_of_synapses.reserve(count);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to open file for reading." << std::endl;
        return list_of_synapses;
    }

    QDataStream in(&file);
    mpz_class number;
    while (list_of_synapses.size() < count && !in.atEnd()) {
        readMpzFromStream(in, number);
        list_of_synapses.push_back(number);
    }

    file.close();
    return list_of_synapses;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Пример использования функции
// QString fileName = "numbers.dat";
// size_t count = 10; // Пример количества чисел для чтения
// std::vector<mpz_class> numbers = readNumbersFromFile2(fileName, count);

// for (const auto &num : numbers) {
//     std::cout << num.get_str() << std::endl;
// }
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//########################################################################################################
    std::cout << "Funktsiya_Resheniya_6" << std::endl;
//########################################################################################################
    return a.exec();
}
