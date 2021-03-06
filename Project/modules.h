#include "systemc.h"
#include "digit.h"

#ifndef _MODULES_H_
#define _MODULES_H_ 1

SC_MODULE (hw_register)
{
	sc_in_clk clk;
	sc_in<NN_DIGIT> in_data;
	sc_in<bool> load_data;
	sc_out<NN_DIGIT> out_data;

	void run_hw_register();

	SC_CTOR (hw_register)
	{
		SC_CTHREAD(run_hw_register, clk.pos());
		out_data.initialize(0);
	}
};

SC_MODULE (hw_register_h)
{
	sc_in_clk clk;
	sc_in<NN_HALF_DIGIT> in_data;
	sc_in<bool> load_data;
	sc_out<NN_HALF_DIGIT> out_data;

	void run_hw_register_h();

	SC_CTOR (hw_register_h)
	{
		SC_CTHREAD(run_hw_register_h, clk.pos());
		out_data.initialize(0);
	}
};

SC_MODULE (hw_splitter)
{
	sc_in<NN_DIGIT> in_data;
	sc_out<NN_DIGIT> out_data_high;
	sc_out<NN_DIGIT> out_data_low;

	void run_hw_splitter();

	SC_CTOR (hw_splitter)
	{
		SC_METHOD(run_hw_splitter);
		sensitive << in_data;
	}
};

SC_MODULE (hw_multiplier)
{
	sc_in<NN_HALF_DIGIT> in_data_1;
	sc_in<NN_DIGIT> in_data_2;
	sc_out<NN_DIGIT> out_data;

	void run_hw_multiplier();

	SC_CTOR (hw_multiplier)
	{
		SC_METHOD(run_hw_multiplier);
		sensitive << in_data_1 << in_data_2;
	}
};

SC_MODULE (hw_adder)
{
	sc_in<NN_DIGIT> in_data_1;
	sc_in<NN_DIGIT> in_data_2;
	sc_out<NN_DIGIT> out_data;

	void run_hw_adder();

	SC_CTOR (hw_adder)
	{
		SC_METHOD(run_hw_adder);
		sensitive << in_data_1 << in_data_2;
	}
};

SC_MODULE (hw_subber)
{
	sc_in<NN_DIGIT> in_data_1;
	sc_in<NN_DIGIT> in_data_2;
	sc_out<NN_DIGIT> out_data;

	void run_hw_subber();

	SC_CTOR (hw_subber)
	{
		SC_METHOD(run_hw_subber);
		sensitive << in_data_1 << in_data_2;
	}
};

SC_MODULE (hw_multiplexor)
{
	sc_in<NN_DIGIT> in_data_1;
	sc_in<NN_DIGIT> in_data_2;
	sc_in<bool> control;
	sc_out<NN_DIGIT> out_data;

	void run_hw_multiplexor();

	SC_CTOR (hw_multiplexor)
	{
		SC_METHOD(run_hw_multiplexor);
		sensitive << in_data_1 << in_data_2 << control;
	}
};

SC_MODULE (hw_to_hh)
{
	sc_in<NN_DIGIT> in_data;
	sc_out<NN_DIGIT> out_data;

	void run_hw_to_hh();

	SC_CTOR (hw_to_hh)
	{
		SC_METHOD(run_hw_to_hh);
		sensitive << in_data;
	}
};

SC_MODULE (hw_hh_extract)
{
	sc_in<NN_DIGIT> in_data;
	sc_out<NN_DIGIT> out_data;

	void run_hw_hh_extract();

	SC_CTOR (hw_hh_extract)
	{
		SC_METHOD(run_hw_hh_extract);
		sensitive << in_data;
	}
};

SC_MODULE (hw_comparator)
{
	sc_in<NN_DIGIT> in_data_reference;
	sc_in<NN_DIGIT> in_data_comparison;
	sc_out<bool> greater_than_signal;

	void run_hw_comparator();

	SC_CTOR (hw_comparator)
	{
		SC_METHOD(run_hw_comparator);
		sensitive << in_data_reference << in_data_comparison;
	}
};


#endif /* end _MODULES_H_ */