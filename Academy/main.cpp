#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, const std::string& birth_date
#define HUMAN_GIVE_PARAMETERS last_name, first_name, birth_date
class Human
{
	const std::string LAST_NAME;
	const std::string FIRST_NAME;
	const tm BIRTH_DATE;

public:
	const std::string& get_last_name() const
	{
		return LAST_NAME;
	}
	const std::string& get_first_name() const
	{
		return FIRST_NAME;
	}
	tm get_birth_date() const
	{
		return BIRTH_DATE;
	}
	int get_age() const
	{
		//1) Получаем текущее время в формате Timestamp
		time_t t_today = time(NULL);
		tm tm_today = *localtime(&t_today);
		//2) Преобразуем дату рождения в формате Timestamp
		tm birth_date = BIRTH_DATE;
		time_t t_birth_date = mktime(&birth_date);

		//3) Находим разницу во времени
		time_t difference = t_today - t_birth_date;

		//4) Преобразуем разницу во времени в формат 'tm'
		tm age = *localtime(&difference);
		age.tm_year -= 70;
		return age.tm_year;
	}
	tm parse_date(const std::string& date)
	{
		char sz_date[32] = {};
		strcpy(sz_date, date.c_str());
		int date_parts[3] = {};
		int n = 0;
		const char delimiters[] = "-./";
		for (char* pch = strtok(sz_date, delimiters); pch; pch = strtok(NULL, delimiters))
			date_parts[n++] = atoi(pch);
		date_parts[0] -= 1900; //структура 'tm' хранит дфту с 1 января 1900 года
		date_parts[1]--; //месяца нумеруются с нуля

		tm tm_birth_date = {};
		tm_birth_date.tm_year = date_parts[0];
		tm_birth_date.tm_mon = date_parts[1];
		tm_birth_date.tm_mday = date_parts[2];
		return tm_birth_date;
	}
	Human(HUMAN_TAKE_PARAMETERS) :
		LAST_NAME(last_name), FIRST_NAME(first_name), BIRTH_DATE(parse_date(birth_date))
	{
		cout << "HConsructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDesructor:\t" << this << endl;
	}
	virtual void info()const
	{
		cout << LAST_NAME << " " << FIRST_NAME << " " << get_age() << endl;
	}
};

class AcademyMember : public Human
{
	std::string speciality;
public:
	const std::string get_speciality()const
	{
		return speciality;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}

#define ACADEMY_MEMBER_TAKE_PARAMETERS const std::string& speciality
#define ACADEMY_MEMBER_GIVE_PARAMETERS speciality
	AcademyMember(HUMAN_TAKE_PARAMETERS,
		ACADEMY_MEMBER_TAKE_PARAMETERS) :
		Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		cout << "AMConstructor:\t" << this << endl;
	}
	~AcademyMember()
	{
		cout << "AMDestructor:\t" << this << endl;
	}
	void info()const override
	{
		Human::info(); //Вызываем метод info() для класса 'Human'
		cout << speciality << endl;
	}
};

#define STUDENT_TAKE_PARAMETERS  const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS group, rating, attendance
class Student : public AcademyMember
{
	std::string group;
	double rating;
	double attendance;

public:
	const std::string& get_group() const
	{
		return group;
	}

	void set_group(const std::string& group)
	{
		this->group = group;
	}

	double get_rating() const
	{
		return rating;
	}

	void set_rating(double rating)
	{
		if (rating >= 0 && rating <= 100)
			this->rating = rating;
	}

	double get_attendance() const
	{
		return attendance;
	}

	void set_attendance(double attendance)
	{
		if (attendance >= 0 && attendance <= 100)
			this->attendance = attendance;
	}

	Student(HUMAN_TAKE_PARAMETERS, ACADEMY_MEMBER_TAKE_PARAMETERS, const std::string& group, double rating, double attendance) :
		AcademyMember(HUMAN_GIVE_PARAMETERS, ACADEMY_MEMBER_GIVE_PARAMETERS)
	{
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}

	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	void info() const override
	{
		AcademyMember::info();
		cout << "Group: " << group << ", Rating: " << rating << "%, Attendance: " << attendance << "%" << endl;
	}
};

#define TEACHER_TAKE_PARAMETERS int experience
#define TEACHER_GIVE_PARAMETERS experience
class Teacher : public AcademyMember
{
	int experience;

public:
	int get_experience() const
	{
		return experience;
	}

	void set_experience(int experience)
	{
		if (experience >= 0)
			this->experience = experience;
	}

	Teacher(HUMAN_TAKE_PARAMETERS, ACADEMY_MEMBER_TAKE_PARAMETERS,
		TEACHER_TAKE_PARAMETERS) :
		AcademyMember(HUMAN_GIVE_PARAMETERS, ACADEMY_MEMBER_GIVE_PARAMETERS)
	{
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}

	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void info() const override
	{
		AcademyMember::info();
		cout << "Experience: " << experience << " years" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
#ifdef  INHERITANCE
	cout << "|| Academy ||" << endl;
	Human human("Тупенко ", "Василий", "2009.09.2");
	human.info();
	AcademyMember am("Тупенко", "Василий", "2000.10.24", "Флуктуации пространства в вакууме");
	am.info();

	Student student("Чухарев", "Матвей", "2009.09.02", "Разработка программного обеспечения", "P_421", 100, 100);
	student.info();

	Teacher teacher("Энштейн", "Альберт", "1979.03.14", "Астрономия", 20);
	teacher.info();
#endif //  INHERITANCE
	Human* group[] =
	{
		new Student("Чухарев", "Матвей", "2009.09.02", "Разработка программного обеспечения", "P_421", 100, 100),
		new Teacher("Энштейн", "Альберт", "1979.03.14", "Астрономия", 20),
		new Student("Гусев", "Савелий", "2010.08.29", "Разработка программного обеспечения", "P_421", 98, 98),
		new Teacher("Олег", "Анатольевич", "1985.01.16", "Разработка программного обеспечения", 16),
		new Student("Львов", "Константин", "2009.09.21", "Разработка программного обеспечения", "P_421", 100, 98),
	};
	cout << sizeof(group) << endl;
	cout << delimiter << endl;
	for (int i = 0; i < sizeof(group)/sizeof(group[0]); i++)
	{
		group[i]->info();
		cout << delimiter << endl;
	}
}