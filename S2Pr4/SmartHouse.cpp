#include <iostream>
#include <string>
#include <fstream>
#include <vector>


enum DeviceType 
{
    INVALID = 0,
    ENERGY_METER = 1,
    SIGNAL_INPUT_UNIT = 2,
    HEATING_CONTROL_UNIT = 3
};


class Device 
{
protected:
    std::string device_name, mod;
    DeviceType type = INVALID;
public:
    virtual void poll() {};

};


namespace EM 
{

    class EnergyMeter : public Device
    {
    public:
        virtual void poll() {}
    };

    class EM_Mercury : public EnergyMeter 
    {
    public:
        EM_Mercury(const std::string& name, const std::string& model) 
        {
            type = ENERGY_METER;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

    class EM_Neva : public EnergyMeter 
    {
    public:
        EM_Neva(const std::string& name, const std::string& model) 
        {
            type = ENERGY_METER;
            device_name = name;
            mod = model;
        }

        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

    class EM_Energomera : public EnergyMeter 
    {
    public:
        EM_Energomera(const std::string& name, const std::string& model) 
        {
            type = ENERGY_METER;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

};

namespace SIU 
{
    class SignalInputUnit : public Device 
    {
    public:
        virtual void poll() {};
    };

    class SI_Reallab : public SignalInputUnit 
    {
    public:
        SI_Reallab(const std::string& name, const std::string& model) 
        {
            type = SIGNAL_INPUT_UNIT;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

    class SI_PElectro : public SignalInputUnit 
    {
    public:
        SI_PElectro(const std::string& name, const std::string& model) 
        {
            type = SIGNAL_INPUT_UNIT;
            device_name = name;
            mod = model;
        }

        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

    class SI_EnergoService : public SignalInputUnit 
    {
    public:
        SI_EnergoService(const std::string& name, const std::string& model) 
        {
            type = SIGNAL_INPUT_UNIT;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }
    };

}



namespace HCU 
{
    class HeatingControlUnit : public Device
    {
    public:
        virtual void poll() {};
    };

    class HCU_Ouman : public HeatingControlUnit 
    {
    public:
        HCU_Ouman(const std::string& name, const std::string& model) 
        {
            type = HEATING_CONTROL_UNIT;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }

    };

    class HCU_Oven : public HeatingControlUnit 
    {
    public:
        HCU_Oven(const std::string& name, const std::string& model) 
        {
            type = HEATING_CONTROL_UNIT;
            device_name = name;
            mod = model;
        }
        void poll() override 
        {
            std::cout << device_name << std::endl;
        }

    };

}



int main() 
{
    std::ifstream f("C:\\Users\\admin\\source\\repos\\P4S2\\P4S2\\devices.txt");
    setlocale(LC_ALL, "RUS");


    if (!f.is_open()) 
    {
        std::cout << "Failed to read device list" << std::endl;
        return -1;
    }
    std::vector<Device*> device_list;
    std::string s, name, model;

    while (f >> s) 
    {
        try 
        {
            switch (s[0]) 
            {
            case '1': 
            {
                name.clear();
                f >> name >> model;

                //EnergyMeter
                if (name == "Меркурий") 
                {
                    EM::EM_Mercury* dev = new EM::EM_Mercury(name, model);
                    device_list.push_back(dev);
                    break;
                }
                if (name == "Нева") 
                {
                    EM::EM_Neva* dev = new EM::EM_Neva(name, model);
                    device_list.push_back(dev);
                    break;
                }
                if (name == "Энергомера") 
                {
                    EM::EM_Energomera* dev = new EM::EM_Energomera(name, model);
                    device_list.push_back(dev);
                    break;
                }

            }
            case '2': 
            {
                name.clear();
                f >> name >> model;

                //SignalInputUnit
                if (name == "Reallab") 
                {
                    SIU::SI_Reallab* dev = new SIU::SI_Reallab(name, model);
                    device_list.push_back(dev);
                    break;
                }
                if (name == "Приборэлектро") 
                {
                    SIU::SI_PElectro* dev = new SIU::SI_PElectro(name, model);
                    device_list.push_back(dev);
                    break;
                }
                if (name == "Энергосервис") 
                {
                    SIU::SI_EnergoService* dev = new SIU::SI_EnergoService(name, model);
                    device_list.push_back(dev);
                    break;
                }
            }

            case '3': 
            {
                name.clear();
                f >> name >> model;

                //HeatingControlUnit
                if (name == "Ouman") 
                {
                    HCU::HCU_Ouman* dev = new HCU::HCU_Ouman(name, model);
                    device_list.push_back(dev);
                    break;
                }
                if (name == "Овен") 
                {
                    HCU::HCU_Oven* dev = new HCU::HCU_Oven(name, model);
                    device_list.push_back(dev);
                    break;
                }
            }
            }
        }
        catch (std::bad_alloc& e) {}
    }

    for (int i = 0; i < device_list.size(); i++) 
    {
        device_list[i]->poll();
    }

    f.close();
    return 0;
}