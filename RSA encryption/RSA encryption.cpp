#include<iostream>
#include<cmath>
#include<string>

using namespace std;

//��'������� ���������� ����������
long p, q, multyple, euler, openGeneratedKey[100], closeGeneratedKey[100], temp[100], digitalMessage[100], encryptedMessage[100], decryptedMessage[100];

//���������������� �������
bool isPrime(long);
void generateKeys();
long multiplicativeInverse(long);
void encrypt(size_t messageLenght);
void decrypt();

int main()
{
    string message;

    //���� ������� �����
    cout << "Enter prime numbers P and Q:";
    cin >> p >> q;

    //�������� �� ������� �� �����
    if (!isPrime(p) || !isPrime(q))
    {
        cout << "Numbers are not prime";
        exit(1);
    }

    //���� ��������� ��� ����������
    cout << "Enter message: ";
    cin.ignore(32767, '\n');
    getline(cin, message);
    cout << message << endl;

    //�������������� ��������� � �������� ���
    for (int i = 0; message[i] != '\0'; i++)
        digitalMessage[i] = message[i];

    //���������� ������������ � ������� ������ �� p � q
    multyple = p * q;
    euler = (p - 1) * (q - 1);

    //��������� �������� � �������� ������
    generateKeys();

    //����� ��������� �������� �������� � �������� ������
    cout << "Possible values of (open key) and (close key) are\n";
    for (int i = 0; i < sqrt(p) - 1; i++)
        cout << openGeneratedKey[i] << "\t" << closeGeneratedKey[i] << "\n";

    //���������� ���������
    encrypt(message.size());
    cout << endl;

    //������������ ���������
    decrypt();

    //����� �������������� ���������
    cout << "The encrypted message is" << endl;
    for (int i = 0; encryptedMessage[i] != -1; i++)
        printf("%c", encryptedMessage[i]);

    //����� ��������������� ���������
    cout << endl << "The decrypted message is" << endl;
    for (int i = 0; decryptedMessage[i] != -1; i++)
        printf("%c", decryptedMessage[i]);

    return 0;
}

//������� ����������� �������� �� ����� �������
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

//�������, ������������ �������� � �������� �����
void generateKeys()
{
    int k = 0;
    for (int i = 2; i < euler; i++)
    {
        if (euler % i == 0)
            continue;

        //���� ����� ������ � �� ����� p � q, �� ��� �������� ����
        if (isPrime(i) && i != p && i != q)
        {
            openGeneratedKey[k] = i;
            long mI = multiplicativeInverse(openGeneratedKey[k]);

            //���� �������� ������� mI ����������, ��������� ��� � �������� ��������� �����
            if (mI > 0)
            {
                closeGeneratedKey[k] = mI;
                k++;
            }

            //���� �������� 99 ��� ������, ������� �� �����
            if (k == 99)
                break;
        }
    }
}

//�������, ����������� ���������������� �������� �����
long multiplicativeInverse(long x)
{
    long int k = 1;

    while (k % x != 0)
        k = k + euler;

    return (k / x);
}

//�������, ���������� ��������� � ������� ��������� �����
void encrypt(size_t messageLength)
{
    long tempP;
    long tempC;
    long key = openGeneratedKey[0];
    int i = 0;

    while (i != messageLength)
    {
        tempP = digitalMessage[i];
        //�������� � ��������� �������� � ��������� �� 1 �� 26
        tempP = tempP - 96;
        long k = 1;

        //������� ������
        for (int j = 0; j < key; j++)
        {
            k = k * tempP;
            k = k % multyple;
        }

        //��������� ������������� �������� � ������ temp
        temp[i] = k;

        //����������� k ������� � ������ � ��������� ��� � ������ encryptedMessage
        tempC = k + 96;
        encryptedMessage[i] = tempC;
        i++;
    }

    //��������� ������ ����� ������(-1) � ������ encryptedMessage
    encryptedMessage[i] = -1;
}

//�������, �������������� ��������� � ������� ��������� �����
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

        //��������� ������
        for (int j = 0; j < key; j++)
        {
            k = k * tempC;
            k = k % multyple;
        }

        //����������� k ������� � ������ ASCII � ��������� ��� � ������ decryptedMessage
        tempP = k + 96;
        decryptedMessage[i] = tempP;
        i++;
    }

    //��������� ������ ����� ������(-1) � ������ encryptedMessage
    decryptedMessage[i] = -1;
}