// Script ��� �ڵ�
// main �ڵ� ��ü�� ���ε�

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Stage.h"
#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Game.h"
#include <ctime> // time() �Լ� ���
#pragma comment(lib, "user32.lib")
int WINDOWWIDTH = 1800;    // �� �ʺ�
int WINDOWHEIGHT = 900;    // �� ����
// �ܼ� ȭ���� ����� �Լ�
void clearConsole() {
    system("cls"); // Windows ����
    // ANSI ǥ�� ��� ��: std::cout << "\033[2J\033[1;1H";
}

void waitForEnter() {
    while (true) {
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // ���� Ű Ȯ��
            break;
        }
    }
}

void printScript(const std::string& script) {
    std::string separator = " ";
    int curPosition = 0;
    int position;

    clearConsole(); // �ܼ� ȭ�� �ʱ�ȭ
    std::cout << "\t\t\t\t\t\t\t\t\t\t\t\tEnter Ű�� �Է��Ͽ� ���" << std::endl;
    for(int i= 1;i<=7;i++)
        std::cout<< "" << std::endl;

    while ((position = script.find(separator, curPosition)) != std::string::npos) {
        int len = position - curPosition;

        // ���� �ܾ� ���
        std::string result = script.substr(curPosition, len);
        std::cout << result << " ";

        Sleep(100); // 0.1�� ���
        curPosition = position + 1;
    }

    // ������ �ܾ� ���
    std::string result = script.substr(curPosition);
    std::cout << result << std::endl;

    // ���� �Է� ���
    waitForEnter();
}
void printTutorialScript(std::string script) {
    std::string seperator = " ";
    int curPosition = 0;
    int position;

    while ((position = script.find(seperator, curPosition)) != std::string::npos) {
        int len = position - curPosition;
        if (GetAsyncKeyState(VK_RETURN)) {
            std::string result = script.substr(curPosition);
            std::cout << result << std::endl << std::endl;
            Sleep(1000);
            return;
        }
        std::string result = script.substr(curPosition, len);
        std::cout << result << " ";
        Sleep(100);
        curPosition = position + 1;
    }

    std::string result = script.substr(curPosition);
    std::cout << result << std::endl << std::endl;

    if (GetAsyncKeyState(VK_RETURN)) {
        return;
    }
    Sleep(1000);
}


void beforeGameScript() {
    printScript("project 1984 ����");
    printScript("1984��, �� ����� �� �ϳ��� ���� �Ʒ� �����߰�, <������ȸ��>�� ��� ���ǰ� ���, ������ �����ϸ� �η��� ���˰� �ִ�.\n�׷��� �̷� ������ ���� �ӿ�����, ������ ������ ����� �ʿ��� ���� �ع� ��ü <�����ع�����>�� ���� ���� �ع��̶�� �� �ϳ��� �ų����� �����ߴ�.\n���� �ٷ� �� �����ع������� ���� ���ְ����� ��¡�� ��������.\n������ ������ �¸��� �̲���°�, ����鿡�� ������ ���� ����� �Ҿ�־���.\n");
    printScript("������ �� ����� ���, ���ο� �ẹ�� ������ ø�ڰ� �츮�� ���� ������ ������װ�, ���� ���� ������ Ư������ ����� �ᱹ �����Ǿ���.\n���� ������ ���� ���� ó�������ν� �� ���迡 ������ ���ǹ��ϴٴ� ������ ������ �Ѵ�.\n�Ѳ� ��ο� ���� �ӿ� ���� ����, ������ ������ �� ��� ����, �������� �����Ѵ�.\n");
    system("cls");
    printTutorialScript(" < Ʃ �� �� �� >");
    printTutorialScript("WASD           : �����¿� �̵� - �ϴ�, �ٴ� ��������");
    printTutorialScript("AD             : �¿� �̵� - �� ��������");
    printTutorialScript("�¿� ����Ű    : Ư�� ���� �߻�ü ���� ����");
    printTutorialScript("Q              : �������� �� �ʻ��, ��Ÿ�� 30��");
    printTutorialScript("E              : �������� �� Ư�� ����, ��Ÿ�� 2�� (�Ϲ� ���� 10���� óġ �� 3�ʰ� ��Ÿ�� 0.2��)");
    printTutorialScript("�������� �̵�  : ���� ���â�� [skymap], [seamap], [landmap] �� ���ϴ� ���������� �Է�  ");
    printTutorialScript("���� Ű        : �̴ϰ��� ���� �� ��ǥ Ű �Է�");
    printTutorialScript("���ŷ� ��ġ�� ���� ���ݿ� �ǰݴ��� ������ 1�� �����ϸ�, ���ŷ� ��ġ�� 0�� �Ǹ� �������� ������ �ɹ� �̴ϰ��ӿ� ����. �ɹ� �̴ϰ����� Ŭ���� �� �ٽ� ���������� �����ϸ�, Ŭ�������� ���� �� ��� ó���Ǵ� �����ϱ� �ٶ���.");
    printTutorialScript("�̴ϰ����� �õ� Ƚ���� �þ���� ���̵��� �����ϴ� �ִ��� �̴ϰ��ӿ� �����ϴ� ��Ȳ�� ���̴� �������� ����ϵ���.");
    printTutorialScript("������������ ������ ���� ���� ������ óġ�ؾ� �Ϲ� ���������� ���������� Ŭ����Ǹ�, ������ óġ�Ͽ� ���踦 ���� ��ȸ�� �־�����.");
    printTutorialScript("������ �ð�����, �ٸ� ������������ ���� ��û�� ���� �ڵ����� ������ ��ȯ�ȴ�.");
    printTutorialScript("������ �Ϲ������� ���� ������ ������ ������ �����Ͽ� �� ������ ���ϱ� �ٶ���.");
    printTutorialScript("Enter Ű�� �Է��Ͽ� ��������");
    waitForEnter();

    system("cls");
}

void badEndingScript() {
    printScript("���� ���� ö�� ���ڿ� ���� �ִ�.\n���� �������� ���� ó������ ������ �ݼӰ� ȭ�� ������ ���� �� �ִ�.\n������ ��¡�ϴ� �����Ͱ� ������ ���� �����ٺ���, ������ȸ���� ������ ���� ������� ���ĵǾ� �ִ�.\n��� ���� �����Ǿ� �ְ�, ���� �̹���ó�� ������.\n������ ���� ����Ǿ���, BIOCOMMANDER-II�� ���������� ��ȣ�� ������ ���Ѵ�.\n�Ʊ��� ���ߴ�.\n������ ������ ���� �ӿ� ������, ������ ��������.");
    printScript("ó������ ������� ������ ���Ҵ�.\nȮ���⿡�� ������ ������ ��Ҹ��� �˸��� �����Ѵ�.\n�������ع������� ���� ���ְ�, ���� ������ ���ϴ� ��, �ݿ���.��\n��Ҹ��� öâ�� Ÿ�� �︮�� ����, ���� ���θ�ĥ �� ����.\n�ո�� �߸��� �ݼ� �����뿡 ������, ����̸� ���� ��ö ������ ���� ���� ���ϰ� �Ѵ�.");
    printScript("7���� ������ ��ȸ�� �㹫�ϰ� �귶��.\n�Ʊ� ����� ������ �ı� ��ȹ�� �����߰�, ������� �����ߴ�.\nBIOCOMMANDER-II�� ���絵 ���복���� �𸥴�.\n���� �� �̻� ������ ��¡�� �ƴϴ�.\n���� �׵��� ���� ó���� ���� ������ ���ǹ��ϴٴ� �޽����� ���� ���̴�.");
    printScript("������ ������ �������.\n��Ҹ��� �͸� ����, �������� ��½�δ�.\n������ �屳�� �̼� ���� ����� ���̰�, ���� ���� ���´�.\n�� �� ��, ��ī�ο� ����� �¸��� �İ���.\n��� ������ ��������, ����� �з��´�.\n");
    printScript("ö�� ��ġ�� ����� �Ѱ����, ���� �׷��� �������.\n������ ������ �̾�����, ����� �ٽ� ������ �� �Ʒ� �����δ�.\n�� ������ ������ �׵��� ���ϴ� �׸� �״�δ�.");
    printScript("Game Over");
}
void goodEndingScript() {
    printScript("���� ���� ���� ���� ������ �� �ִ�.\n�� �μ� ö�� ƴ���� ����� ������ �ܱⰡ �������� �����ϴ�.\n������ ������ ����θ� �ı��ϸ�, ������ ��¡�� ������� ������ ���̾��� ������ Der Kaiser�� ��ħ�� ħ���ߴ�.\n������� �Լ��� �� ������ �޾Ƹ�ġ��, ���� ����� �ұ� ���̸� �հ� ���ĳ��� ���� ������� �ѿ� Ȳȥ�� ������ �޷��´�.\n");
    printScript("������ �� �������� ������ ����� ���� ���ϴ� ����, ������ �ع������� ������ ����� ������ �ϰ� �ִ�.\nBIOCOMMANDER-II�� ���� ���뽺���� �����ؿ� ���� 7���� ����� �Ӹ����� ��ģ��.\n�ð��� ü��, �׸��� ���ŷ±��� ����� ��Ȳ������ �츮�� �̷� �¸���.\n���� �����δ� ��������, ���� �� ����ϴ� �ϰ��� �����ġ�� ��ħ�� ���߾���.\n");
    printScript("���� �����θ� ��¡�ϴ� ������ �屳�� ������ ������ ��, ���� ������ ������ �ҽ����� �ڼ��� �־���.\n�츮�� �̷� ���� �ܼ��� ������ �¸��� �Ѿ�, ������ ���� ��� �Ʒ� �����̴� ���踦 ���� ��ȣ��.\n�ұ��� ����������, �츮�� ������ ���� ���� �ٽ� ���� ���̴�.\n�𿩵�� �ع����� ������� ������ ���� ������� ���� �� �ִ�.\n��� ����, ���, ����� �ʿ��� '�ΰ��ٿ� ��'�� ��ã������ ������ �� ������ ��Ÿ�� �ִ�.\n");
    printScript("���� ������ BIOCOMMANDER-II�� �����۰Ÿ���.\n�� ��ġ�� �� �̻� ������ ���� ��ȣ�� ������ �ʿ䰡 ����.\n��ħ�� �� ��ο� ���� �ӿ��� ������ �Ǿ���, �ݼ� ������ �����ϴ� ó������ ������ ������ ���̴�.\n���� ���� �ź��� ������.\n���忡 ���� ������� ���� ���� ȯȣ�� ������, ���� �����ϸ� ������ �ɾ����.\n");
    printScript("�ٱ� �ϴ��� �������� ���� ���ϴ�.\n������ ������ ���ǰ� �� �� �̻� ���踦 ���� �� ���� �Ǿ�����, �츮�� �¸����� ������ �ִ�.\n���� �ų�� ����, ����� ���� ������ �� ������ ���ǻ��, ���ο� ������ ���� ���̴�.\n����, ����, �ΰ����� ��Ƽ����� ���踦 ����.\n");
    printScript("���� ���� �ָ��� ��� ������ ����.\n�ڸ� ���ƺ� �ʿ䰡 ����.\n���� �����̴�.\n�츮�� �ع��� �̷�����.");
}



int main() {

    srand(static_cast<unsigned>(time(0))); // ���� �������� seed�� ���� �ð����� ����
    sf::Event event;

    beforeGameScript();

    Game game;
    bool goodEnding = game.run();
    if (goodEnding) goodEndingScript();
    else  badEndingScript();

    return 0;
}
