#include <iostream>
#include <iomanip>

class CAR
{
	private:
		int is_engine_on;
		double trip;
		double mileage;
		double tank_capacity;
		double fuel;
		double fuel_usage;
		double range;
		
		void calculate_range()
		{
			range = fuel/fuel_usage;
		}

	protected:
		void present()
		{
			calculate_range();
			if (is_engine_on == 1)
				std::cout << "Stan: silnik wlaczony\n";
			else
				std::cout << "Stan: silnik wylaczony\n";
				
			std::cout << "Pojemnosc baku: " << tank_capacity << "l\n";
			std::cout << "Ilosc paliwa w baku: " << fuel << "l\n";
			std::cout << "Zasieg: " << std::setprecision(5) << range << "km\n";
			std::cout << "Srednie spalanie: " << fuel_usage*100<< "l/100km\n";
			std::cout << "Przebieg: " << mileage << "km\n";	
		}
		
	public:
		CAR()
		{
			is_engine_on = 0;
			trip = 0;
			std::cout<<"Obecny przebieg (km): ";
			std::cin>>mileage;
			std::cout<<"Pojemnosc baku (l): ";
			std::cin>>tank_capacity;
			std::cout<<"Ilosc paliwa (l): ";
			std::cin>>fuel;
			std::cout<<"Srednie spalanie (l/100km): ";
			std::cin>>fuel_usage;
			fuel_usage /= 100;
		};
	
		~CAR()
		{
		};
	
		
		void start_engine()
		{
			if (is_engine_on == 1)
				std::cout << "Silnik jest juz uruchomiony!" << "\n";
			else if (is_engine_on == 0 && fuel == 0)
			{
				is_engine_on = 0;
				std::cout << "Nie mozna uruchomic silnika - brak paliwa!" << "\n";
			}
			else
			{
				is_engine_on = 1;
				calculate_range();
	
				std::cout << "Uruchomiono silnik." << "\n";
			}
		}
	
		void stop_engine()
		{
			if (is_engine_on == 0)
				std::cout << "Silnik jest juz wylaczony!" << "\n";
			else
			{
				is_engine_on = 0;
				std::cout << "Wylaczono silnik." << "\n";
			}
		}
	
		void refuel()
		{
			if (is_engine_on == 1)
				std::cout << "Najpierw zatrzymaj silnik!\n";
			else
			{
				if (fuel==tank_capacity)
				{
					std::cout << "Masz pelen bak!\n";
				}
				else
				{
					double max = tank_capacity-fuel;
					double how_much;
					std::cout << "Ile litrow zatankowac? (Do pelna brakuje " << max << "l.)\n";
					std::cin >> how_much;
					while (how_much > max || how_much < 0)
					{
						std::cout << "Nie mozna tyle wtankowac. Wybierz inna wartosc:\n";
						std::cin >> how_much;
					}
					fuel +=how_much;
					std::cout << "Zatankowano " << how_much << "l paliwa.\n";
				}
				calculate_range();
				std::cout << "Obecny zasieg to " << std::setprecision(5) << range << "km.\n";
			}
		}
	
		void drive()
		{
			if (is_engine_on == 0)
				std::cout << "Najpierw uruchom silnik!\n";
			else
			{
				double km;
				std::cout << "Ile km chcesz przejechac?\n";
				std::cin >> km;
	
				calculate_range();
				if (km < 0)
					std::cout << "Dystans nie moze byc ujemny!\n";
				else if (km > range)
				{
					std::cout << "Nie ma wystarczajaco duzo paliwa.\n";
					std::cout << "Obecny zasieg to " << std::setprecision(5) << range << "km.\n";
					std::cout << "Wybierz co chcesz zrobic:\n";
					int a;
					std::cout << "  1 - jedz mimo to\n";
					std::cout << "  2 - wylacz silnik, zatankuj i wtedy jedz\n";
					std::cout << "  3 - rezygnuj\n";
					std::cin >> a;
					switch (a)
					{
					case 1:
						trip = range;
						mileage += range;
						stop_engine();
						break;
					case 2:
						stop_engine();
						refuel();
						start_engine();
						drive();
						break;
					case 3:
						break;
					}
				}
				else if (km >= 0 && km <= range)
				{
					trip = km;
					mileage += km;
				}
				fuel -= trip*fuel_usage;
				calculate_range();
				std::cout << "Przejechano " << trip << "km.\n";
				std::cout << "Pozostaly zasieg - " << std::setprecision(5) << range << "km.\n";
				std::cout << "Pozostale paliwo - " << fuel << "l.\n";
			}
		}
};
/////////////////////////////////////////////////////////////////////
class PERSONAL: public CAR
{
	private:
		int seats;
		
	public:
		PERSONAL(): CAR()
		{
			std::cout <<"Liczba miejsc: ";
			std::cin>>seats;
		};
		~PERSONAL()
		{
		};
		
		void present()
		{
			CAR::present();
			std::cout << "Ilosc miejsc: " << seats << "\n";
		}
		
		void set_seats(int number)
		{
			if(number>0)
				seats = number;
			else
				std::cout << "Liczba miejsc musi byc wieksza od 0.\n";
		}
		
		int get_seats()
		{
			return seats;
		}
};
/////////////////////////////////////////////////////////////////////
class TRUCK: public CAR
{
	private:
		double max_capacity;
		double capacity;
		std::string cargo;
	protected:
		
	public:
		TRUCK(): CAR()
		{
			std::cout <<"Ladownosc (t): ";
			std::cin >>max_capacity;
			std::cout <<"Ilosc ladunku (t): ";
			std::cin >>capacity;
			std::cout <<"Typ ladunku: ";
			std::cin >> cargo;
		};
		~TRUCK()
		{
		};
		
		void load()
		{
			if(capacity == max_capacity)
			{
				std::cout << "Brak miejsca! Samochod jest pelen!\n";
			}
			else
			{
				double to_load;
				double space = max_capacity-capacity;
				if(capacity==0)
				{
					std::cout << "Podaj ladunek:\n";
					std::cin >> cargo;
				}
				std::cout << "Ile chcesz zaladowac? (Do pelna brakuje " << space << "t.)\n";
				std::cin >> to_load;
				while(to_load<0 || to_load>max_capacity)
				{
					std::cout << "Niepoprawna wartosc. Podaj poprawna wartosc:\n";
					std::cin >> to_load;
				}
				capacity += to_load;
				std::cout << "Zaladowano " << to_load << "t.\n";
			}
		}
		
		void unload()
		{
			if(capacity==0)
			{
				std::cout << "Brak ladunku do rozladowania!";
			}
			else
			{
				double to_unload;
				std::cout << "Ile chcesz rozladowac? (Obecna ilosc ladunku: "<< capacity <<" t)\n";
				std::cin >> to_unload;
				while(to_unload<0 || to_unload>capacity)
				{
					std::cout << "Niepoprawna wartosc. Podaj poprawna wartosc:\n";
					std::cin >> to_unload;
				}
				capacity -= to_unload;
				std::cout << "Rozladowano " << to_unload << "t.\n";
				if(capacity==0)
				{
					cargo = "-";
				}
			}
		}
		
		void present()
		{
			CAR::present();
			std::cout << "Ladownosc: " << max_capacity << "t\n";
			std::cout << "Ilosc ladunku: " << capacity << "t\n";
			std::cout << "Ladunek: " << cargo << "\n";
		}
};
////////////////////////////////////////////////////////////////////

int main()
{
	int start;
	int choice;
	
	do{
		std::cout << "Wybierz pojazd:"<< "\n";
		std::cout << "  " << "1 - Samochod osobowy\n";
		std::cout << "  " << "2 - Samochod ciezarowy\n";
		std::cout << "  " << "0 - Wyjdz\n";
		std::cin >> start;
		
		switch (start)
		{
			case 0:
				break;
			case 1:
				{
					PERSONAL car1;
					do
					{
						std::cout << "\n" << "Wybierz co chcesz zrobic:" << "\n";
						std::cout << "  " << "1 - Uruchom silnik\n";
						std::cout << "  " << "2 - Zatrzymaj silnik\n";
						std::cout << "  " << "3 - Jedz\n";
						std::cout << "  " << "4 - Tankuj\n";
						std::cout << "  " << "5 - Prezentuj stan\n";
						std::cout << "  " << "6 - Zmien liczbe miejsc\n";
						std::cout << "  " << "7 - Pobierz liczbe miejsc\n";
						std::cout << "  " << "0 - Zakoncz pokaz\n";
						std::cin >> choice;
						
						switch (choice)
						{
							case 0:
								break;
							case 1:
								car1.start_engine();
								break;
							case 2:
								car1.stop_engine();
								break;
							case 3:
								car1.drive();
								break;
							case 4:
								car1.refuel();
								break;
							case 5:
								car1.present();
								break;
							case 6:
								int number_of_seats;
								std::cout << "Podaj liczbe miejsc: ";
								std::cin >> number_of_seats;
								car1.set_seats(number_of_seats);
								break;
							case 7:
								std::cout << "Obecna liczba miejsc: " << car1.get_seats() << "\n";
						}	
					} while (choice != 0);
					std::cout << "\n";
				
					break;	
				}
			case 2:
				{	
					TRUCK car2;
					do
					{
						std::cout << "\n" << "Wybierz co chcesz zrobic:" << "\n";
						std::cout << "  " << "1 - Uruchom silnik\n";
						std::cout << "  " << "2 - Zatrzymaj silnik\n";
						std::cout << "  " << "3 - Jedz\n";
						std::cout << "  " << "4 - Tankuj\n";
						std::cout << "  " << "5 - Prezentuj stan\n";
						std::cout << "  " << "6 - Laduj\n";
						std::cout << "  " << "7 - Rozladuj\n";
						std::cout << "  " << "0 - Zakoncz pokaz\n";
						std::cin >> choice;
						
						switch (choice)
						{
							case 0:
								break;
							case 1:
								car2.start_engine();
								break;
							case 2:
								car2.stop_engine();
								break;
							case 3:
								car2.drive();
								break;
							case 4:
								car2.refuel();
								break;
							case 5:
								car2.present();
								break;
							case 6:
								car2.load();
								break;
							case 7:
								car2.unload();
								break;
						}
					} while (choice != 0);
					
					break;
				}
		}
	} while(start != 0);
}

