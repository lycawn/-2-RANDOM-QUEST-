#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <vector>   


std::string generateQuestName() {
    std::string names[] = { "Power Training", "The Ancient Relic", "The Lost Artifact", "The Dark Forest", "The Crystal Cavern" };
    int index = rand() % (sizeof(names) / sizeof(names[0]));
    return names[index];
}


int generateKillCount() {
    return rand() % 10 + 5;
}


int generateDuration() {
    return rand() % 10 + 1; 
}


std::string generateRandomText() {
    std::vector<std::string> words = { "Hello", "Greetings", "Welcome", "Good day", "Salutations", "Howdy" };
    std::string text = "";
    int numWords = rand() % 5 + 1;
    for (int i = 0; i < numWords; ++i) {
        int index = rand() % words.size();
        text += words[index];
        if (i < numWords - 1) {
            text += " ";
        }
    }
    return text;
}

int main() {
    srand(time(0));


    std::string questName = generateQuestName();
    int killCount = generateKillCount();
    int randomLevel = rand() % 85 + 1;
    int duration = generateDuration();
    int mobVnum;
    int keySelection;
    int countNum = 0;
    int VALUE;
    std::string STAT1 = "";
    std::string randomText = generateRandomText();
    std::vector<std::string> STATS =
    {
                "DEF_GRADE_BONUS"
                "ATTBONUS_HUMAN",
        "ATTBONUS_MONSTER",
        "ATTBONUS_DEVIL",
        "ATTBONUS_ANIMAL",
        "ATTBONUS_ORC",
        "STEAL_HP",
        "CRITICAL_PCT",
        "PENETRATE_PCT",
        "MAX_HP",
        "CON",
        "INT",
        "DEX",
        "STR",
        "ATT_SPEED",
        "MOV_SPEED",
        "CAST_SPEED",
        "HP_REGEN",
        "POISON_PCT"
        "RESIST_SWORD",
        "RESIST_TWOHAND",
        "RESIST_DAGGER",
        "RESIST_BOW",
        "RESIST_WIND",
        "RESIST_MAGIC",
        "RESIST_ELEC",
        "RESIST_FIRE",
        "REFLECT_MELEE",
        "POISON_REDUCE",
        "NORMAL_HIT_DAMAGE_BONUS",
        "SKILL_DAMAGE_BONUS",
        "NORMAL_HIT_DEFEND_BONUS",
        "SKILL_DEFEND_BONUS",
        "MAX_HP_PCT"

    };



    std::ofstream outFile("randomquest.lua");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing\n";
        return 1;
    }
    std::cout << "=====LYARCHONS RANDOM QUEST GENERATOR=====" << std::endl;
    std::cout << "Enter mob Vnum of prefered mob" << std::endl;  
    std::cin >> mobVnum;
    std::cout << "Choose reward quest bonus stat" << std::endl; 
    for (auto val : STATS)
    {
        countNum++;
       std:: cout << "[" << countNum << "]" << val <<  std::endl;
    }
    std::cin >> keySelection;
    STAT1 = STATS.at(keySelection - 1);

    std::cout << " Enter your STAT BONUS value " << std::endl;
    std::cin >> VALUE;

    outFile << "quest " << questName << " begin\n";
    outFile << "\tstate start begin\n";
    outFile << "\t\twhen login or levelup with pc.get_level() >= "<< randomLevel <<" begin\n";
    outFile << "\t\t\tsend_letter(\"" << questName << "\")\n";
    outFile << "\t\tend\n";
    outFile << "\t\twhen button or info begin\n";
    outFile << "\t\t\tsay_title(\"PvP Mission\")\n";
    outFile << "\t\t\tsay(\"" << randomText << " \" .. pc.get_name() << \",\")\n";
    outFile << "\t\t\tsay(\"I see you are weak & need some training.\")\n";
    outFile << "\t\t\tsay(\"No problem at all i will help you\")\n";
    outFile << "\t\t\tsay(\"on the path to becoming a great warrior!\")\n";
    outFile << "\t\t\twait()\n";
    outFile << "\t\t\tsay_title(\"" << questName << "\")\n";
    outFile << "\t\t\tsay(\"Defeat a total of " << killCount << " metins\")\n";
    outFile << "\t\t\tsay(\"[ENTER]Of course, I will reward you as well!\")\n";
    outFile << "\t\t\tset_state(pvpquest1)\n";
    outFile << "\t\tend\n";
    outFile << "\tend\n";
    outFile << "\tstate pvpquest1 begin\n";
    outFile << "\t\twhen letter begin\n";
    outFile << "\t\t\tsend_letter(\"Mission to greatness\")\n";
    outFile << "\t\tend\n";
    outFile << "\t\twhen button or info begin\n";
    outFile << "\t\t\tsay_title(\"Your First Mission\")\n";
    outFile << "\t\t\tsay(\"Destroy a total of " << killCount << " metins \")\n";
    outFile << "\t\t\tsay()\n";
    outFile << "\t\t\tsay_reward(\"You have killed \" .. pc.getqf(\"kills\") << \" out of " << killCount << ".\")\n";
    outFile << "\t\t\twait()\n";
    outFile << "\t\t\tsend_letter(\"Your First Mission\")\n";
    outFile << "\t\tend\n";
    outFile << "\t\twhen kill with "<< mobVnum <<" begin\n";
    outFile << "\t\t\tpc.setqf(\"kills\", pc.getqf(\"kills\") + 1)\n";
    outFile << "\t\t\tif pc.getqf(\"kills\") >= " << killCount << " then\n";
    outFile << "\t\t\t\tpc.delqf(\"kills\")\n";
    outFile << "\t\t\t\tnotice_all(pc.get_name() .. \" has completed the first mission!\")\n";
    outFile << "\t\t\t\tsay_title(\"You have successfully completed the first mission\")\n";
    outFile << "\t\t\t\taffect.add_collect(apply."<< STAT1 <<", "<< VALUE <<", 60 * 60 * 24 * 365 * " << duration << ")\n";
    outFile << "\t\t\t\tsay(\"[ENTER]You receive:\")\n";
    outFile << "\t\t\t\tsay_reward(\"+50HP Permanent.\")\n";
    outFile << "\t\t\t\tsay_reward(\"+2Defense Permanent\")\n";
    outFile << "\t\t\t\tpc.delqf(\"kills\")\n";
    outFile << "\t\t\t\tset_state(__COMPLETE__)\n";
    outFile << "\t\t\t\tif pc.is_gm() then\n";
    outFile << "\t\t\t\t\tpc.setqf(\"daily_quest\", get_time() + 10)\n";
    outFile << "\t\t\t\telse\n";
    outFile << "\t\t\t\t\tpc.setqf(\"daily_quest\", get_time() + 24 * 60 * 60)\n";
    outFile << "\t\t\t\tend\n";
    outFile << "\t\t\t\trestart_quest()\n";
    outFile << "\t\t\telse\n";
    outFile << "\t\t\t\tclear_letter()\n";
    outFile << "\t\t\tend\n";
    outFile << "\t\tend\n";
    outFile << "\tend\n";
    outFile << "\tstate __COMPLETE__ begin\n";
    outFile << "\tend\n";
    outFile << "end\n";


    // Close file
    outFile.close();

    std::cout << "Random quest script generated and saved to randomquest.lua\n";
    std::cout << "Everything is free , but you can always buy me a coffee and find out more products at https://buymeacoffee.com/angelosant" << std::endl;

    return 0;
}
