#include <iostream>
using namespace std;
class ComputerParts {
private:
    int cpuStock, gpuStock, ramStock, ssdStock,
	motherboardStock, coolerStock, keyboardStock,
	mouseStock, monitorStock, laptopStock;

    double cpuPrice, gpuPrice, ramPrice, ssdPrice,
	   motherboardPrice, coolerPrice, keyboardPrice,
	   mousePrice, monitorPrice, laptopPrice;

    double totalPrice;

public:
    ComputerParts(int initialCpuStock, int initialGpuStock, int initialRamStock, int initialSsdStock,
		  int initialMotherboardStock, int initialCoolerStock, int initialKeyboardStock,
		  int initialMouseStock, int initialMonitorStock, int initialLaptopStock)
    : cpuStock(initialCpuStock), gpuStock(initialGpuStock), ramStock(initialRamStock), ssdStock(initialSsdStock),
      motherboardStock(initialMotherboardStock), coolerStock(initialCoolerStock), keyboardStock(initialKeyboardStock),
      mouseStock(initialMouseStock), monitorStock(initialMonitorStock), laptopStock(initialLaptopStock),
      cpuPrice(50000.0), gpuPrice(35000.0), ramPrice(8000.0), ssdPrice(15000.0),
      motherboardPrice(16000.0), coolerPrice(2500.0), keyboardPrice(2000.0),
      mousePrice(1000.0), monitorPrice(45000.0), laptopPrice(55000.0),
      totalPrice(0.0) {}

    void displayMenu() {
	cout << "Computer Parts Menu:" << endl;
	cout << "1. CPU" << endl;
	cout << "2. GPU" << endl;
	cout << "3. RAM" << endl;
	cout << "4. SSD" << endl;
	cout << "5. Motherboard" << endl;
	cout << "6. Cooler" << endl;
	cout << "7. Keyboard" << endl;
	cout << "8. Mouse" << endl;
	cout << "9. Monitor" <<endl;
	cout << "10. Laptop" << endl;
	cout << "11. Display Selected Parts" << endl;
	cout << "Enter your choice (1-11): ";
    }

    void purchaseCPU(int quantity) {
	if (quantity > cpuStock) {
	    cout << "Sorry, not enough CPUs." << endl;
	} else {
	    cpuStock -= quantity;
	    totalPrice += quantity * cpuPrice;
	    cout << "You purchased " << quantity << " CPUs for Rs" << quantity * cpuPrice << endl;
	}
    }

    void purchaseGPU(int quantity) {
	if (quantity > gpuStock) {
	    cout << "Sorry, not enough GPUs." << endl;
	} else {
	    gpuStock -= quantity;
	    totalPrice += quantity * gpuPrice;
	    cout << "You purchased " << quantity << " GPUs for Rs" << quantity * gpuPrice <<endl;
	}
    }

    void purchaseRAM(int quantity) {
	if (quantity > ramStock) {
	    cout << "Sorry, not enough RAM." << endl;
	} else {
	    ramStock -= quantity;
	    totalPrice += quantity * ramPrice;
	    cout << "You purchased " << quantity << " RAM units for Rs" << quantity * ramPrice << endl;
	}
    }

    void purchaseSSD(int quantity) {
	if (quantity > ssdStock) {
	    cout << "Sorry, not enough SSDs." << endl;
	} else {
	    ssdStock -= quantity;
	    totalPrice += quantity * ssdPrice;
	    cout << "You purchased " << quantity << " SSDs for Rs" << quantity * ssdPrice << endl;
	}
    }

    void purchaseMotherboard(int quantity) {
	if (quantity > motherboardStock) {
	    cout << "Sorry, not enough motherboards." << endl;
	} else {
	    motherboardStock -= quantity;
	    totalPrice += quantity * motherboardPrice;
	    cout << "You purchased " << quantity << " motherboards for Rs" << quantity * motherboardPrice << endl;
	}
    }

    void purchaseCooler(int quantity) {
	if (quantity > coolerStock) {
	    cout << "Sorry, not enough coolers." << endl;
	} else {
	    coolerStock -= quantity;
	    totalPrice += quantity * coolerPrice;
	    cout << "You purchased " << quantity << " coolers for Rs" << quantity * coolerPrice << endl;
	}
    }

    void purchaseKeyboard(int quantity) {
	if (quantity > keyboardStock) {
	    cout << "Sorry, not enough keyboards." << endl;
	} else {
	    keyboardStock -= quantity;
	    totalPrice += quantity * keyboardPrice;
	    cout << "You purchased " << quantity << " keyboards for Rs" << quantity * keyboardPrice << endl;
	}
    }

    void purchaseMouse(int quantity) {
	if (quantity > mouseStock) {
	    cout << "Sorry, not enough mice." << endl;
	} else {
	    mouseStock -= quantity;
	    totalPrice += quantity * mousePrice;
	    cout << "You purchased " << quantity << " mice for Rs" << quantity * mousePrice << endl;
	}
    }

    void purchaseMonitor(int quantity) {
	if (quantity > monitorStock) {
	    cout << "Sorry, not enough monitors." << endl;
	} else {
	    monitorStock -= quantity;
	    totalPrice += quantity * monitorPrice;
	    cout << "You purchased " << quantity << " monitors for Rs" << quantity * monitorPrice << endl;
	}
    }

    void purchaseLaptop(int quantity) {
	if (quantity > laptopStock) {
	    cout << "Sorry, not enough laptops." << endl;
	} else {
	    laptopStock -= quantity;
	    totalPrice += quantity * laptopPrice;
	    cout << "You purchased " << quantity << " laptops for Rs" << quantity * laptopPrice << endl;
	}
    }

    void displaySelectedParts() {
	cout << "Selected Parts: " << endl;
	cout << "Total Price: Rs" << totalPrice << endl;
    }

    void displayRemainingStock() {
	cout << "Remaining Stock:" << endl;
	cout << "CPU: " << cpuStock << endl;
	cout << "GPU: " << gpuStock << endl;
	cout << "RAM: " << ramStock << endl;
	cout << "SSD: " << ssdStock << endl;
	cout << "Motherboard: " << motherboardStock << endl;
	cout << "Cooler: " << coolerStock << endl;
	cout << "Keyboard: " << keyboardStock << endl;
	cout << "Mouse: " << mouseStock << endl;
	cout << "Monitor: " << monitorStock << endl;
	cout << "Laptop: " << laptopStock << endl;
    }
};

int main() {
    int CpuStock, GpuStock, RamStock, SsdStock,
	MotherboardStock, CoolerStock, KeyboardStock,
	MouseStock, MonitorStock, LaptopStock;

    

    cout<<"-------Welcome to Computer Shop-------";

    cout << "\nEnter stock for CPU: ";
    cin >> CpuStock;

    cout << "Enter stock for GPU: ";
    cin >> GpuStock;

    cout << "Enter stock for RAM: ";
    cin >> RamStock;

    cout << "Enter stock for SSD: ";
    cin >> SsdStock;

    cout << "Enter stock for Motherboard: ";
    cin >> MotherboardStock;

    cout << "Enter stock  Cooler: ";
    cin >> CoolerStock;

    cout << "Enter stock for Keyboard: ";
    cin >> KeyboardStock;

    cout << "Enter stock for Mouse: ";
    cin >> MouseStock;

    cout << "Enter stock for Monitor: ";
    cin >> MonitorStock;

    cout << "Enter stock for Laptop: ";
    cin >> LaptopStock;

    char buyagain;
    int choice;
    int quantity;

    ComputerParts parts(CpuStock, GpuStock, RamStock, SsdStock,
			MotherboardStock, CoolerStock, KeyboardStock,
			MouseStock, MonitorStock, LaptopStock);

    do {
	parts.displayMenu();
	cin >> choice;

	switch (choice) {
	    case 1:
		cout << "Enter quantity for CPU: ";
		cin >> quantity;
		parts.purchaseCPU(quantity);
		break;

	    case 2:
		cout << "Enter quantity for GPU: ";
		cin >> quantity;
		parts.purchaseGPU(quantity);
		break;

	    case 3:
	       cout << "Enter quantity for RAM: ";
		cin >> quantity;
		parts.purchaseRAM(quantity);
		break;

	    case 4:
		cout << "Enter quantity for SSD: ";
		cin >> quantity;
		parts.purchaseSSD(quantity);
		break;

	    case 5:
		cout << "Enter quantity for Motherboard: ";
		cin >> quantity;
		parts.purchaseMotherboard(quantity);
		break;

	    case 6:
		cout << "Enter quantity for Cooler: ";
		cin >> quantity;
		parts.purchaseCooler(quantity);
		break;

	    case 7:
		cout << "Enter quantity for Keyboard: ";
		cin >> quantity;
		parts.purchaseKeyboard(quantity);
		break;

	    case 8:
		cout << "Enter quantity for Mouse: ";
		cin >> quantity;
		parts.purchaseMouse(quantity);
		break;

	    case 9:
		cout << "Enter quantity for Monitor: ";
		cin >> quantity;
		parts.purchaseMonitor(quantity);
		break;

	    case 10:
		cout << "Enter quantity for Laptop: ";
		cin >> quantity;
		parts.purchaseLaptop(quantity);
		break;

	    case 11:
		parts.displaySelectedParts();
		break;

	    default:
		cout << "Invalid choice. Please select a valid option." << endl;
	}

	cout << "Do you want to buy more parts? (y/n): ";
	cin >> buyagain;
    } while (buyagain == 'y' || buyagain == 'Y');

    parts.displayRemainingStock();

    

    return 0;
}
