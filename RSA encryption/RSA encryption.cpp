#include<iostream>
#include<cmath>
#include<string>

using namespace std;

//Об'явлегие глобальных переменных
long p, q, multyple, euler, openGeneratedKey[100], closeGeneratedKey[100], temp[100], digitalMessage[100], encryptedMessage[100], decryptedMessage[100];

//Прототипирование функций
bool isPrime(long);
void generateKeys();
long multiplicativeInverse(long);
void encrypt(size_t messageLenght);
void decrypt();

int main()
{
    string message;

    //Ввод простых чисел
    cout << "Enter prime numbers P and Q:";
    cin >> p >> q;

    //Проверка на простые ли числа
    if (!isPrime(p) || !isPrime(q))
    {
        cout << "Numbers are not prime";
        exit(1);
    }

    //Ввод сообщения для шифрования
    cout << "Enter message: ";
    cin.ignore(32767, '\n');
    getline(cin, message);
    cout << message << endl;

    //Преобразование сообщения в цифровой вид
    for (int i = 0; message[i] != '\0'; i++)
        digitalMessage[i] = message[i];

    //Вычисление произведения и функции Эйлера от p и q
    multyple = p * q;
    euler = (p - 1) * (q - 1);

    //Генерация открытых и закрытых ключей
    generateKeys();

    //Вывод возможных значений открытых и закрытых ключей
    cout << "Possible values of (open key) and (close key) are\n";
    for (int i = 0; i < sqrt(p) - 1; i++)
        cout << openGeneratedKey[i] << "\t" << closeGeneratedKey[i] << "\n";

    //Шифрование сообщения
    encrypt(message.size());
    cout << endl;

    //Дешифрование сообщения
    decrypt();

    //Вывод зашифрованного сообщения
    cout << "The encrypted message is" << endl;
    for (int i = 0; encryptedMessage[i] != -1; i++)
        printf("%c", encryptedMessage[i]);

    //Вывод расшифрованного сообщения
    cout << endl << "The decrypted message is" << endl;
    for (int i = 0; decryptedMessage[i] != -1; i++)
        printf("%c", decryptedMessage[i]);

    return 0;
}

//Функция определения является ли число простым
bool isPrime(long pr)
{
    double j = sqrt(pr);
    for (int i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return false;
    }
    return true;
}

//Функция, генерирующая открытые и закрытые ключи
void generateKeys()
{
    int k = 0;
    for (int i = 2; i < euler; i++)
    {
        if (euler % i == 0)
            continue;

        //Если число просто и не равно p и q, то это открытый ключ
        if (isPrime(i) && i != p && i != q)
        {
            openGeneratedKey[k] = i;
            long mI = multiplicativeInverse(openGeneratedKey[k]);

            //Если обратный элемент mI существует, сохраняем его в качестве закрытого ключа
            if (mI > 0)
            {
                closeGeneratedKey[k] = mI;
                k++;
            }

            //Если получено 99 пар ключей, выходим из цикла
            if (k == 99)
                break;
        }
    }
}

//Функции, вычисляющая мультипликативно обратное число
long multiplicativeInverse(long x)
{
    long int k = 1;

    while (k % x != 0)
        k = k + euler;

    return (k / x);
}

//Функция, шифрования сообщения с помощью открытого ключа
void encrypt(size_t messageLength)
{
    long tempP;
    long tempC;
    long key = openGeneratedKey[0];
    int i = 0;

    while (i != messageLength)
    {
        tempP = digitalMessage[i];
        //Приводим к числовому значению в диапазоне от 1 до 26
        tempP = tempP - 96;
        long k = 1;

        //Шифруем символ
        for (int j = 0; j < key; j++)
        {
            k = k * tempP;
            k = k % multyple;
        }

        //Сохраняем зашифрованное значение в массив temp
        temp[i] = k;

        //Преобразуем k обратно в символ и сохраняем его в массив encryptedMessage
        tempC = k + 96;
        encryptedMessage[i] = tempC;
        i++;
    }

    //Добавляем маркер конца строки(-1) в массив encryptedMessage
    encryptedMessage[i] = -1;
}

//Функция, расшифровывает сообщение с помощью закрытого ключа
void decrypt()
{
    long tempP;
    long tempC;
    long key = closeGeneratedKey[0];
    int i = 0;

    while (encryptedMessage[i] != -1)
    {
        tempC = temp[i];
        long k = 1;

        //Дешифруем символ
        for (int j = 0; j < key; j++)
        {
            k = k * tempC;
            k = k % multyple;
        }

        //Преобразуем k обратно в символ ASCII и сохраняем его в массив decryptedMessage
        tempP = k + 96;
        decryptedMessage[i] = tempP;
        i++;
    }

    //Добавляем маркер конца строки(-1) в массив encryptedMessage
    decryptedMessage[i] = -1;
}