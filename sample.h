


class Sample
{
private:
	double value;
	Sample *next;

public:
	Sample(Sample* next, double val);
	~Sample();
};
