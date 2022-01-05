#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "modules.h"

SC_MODULE (dh_hw)
{

  //Port definitions
  sc_in_clk clk;
  sc_in <NN_DIGIT> from_sw0, from_sw1, from_sw2;
  sc_in <NN_HALF_DIGIT> from_sw3;
  sc_out <NN_HALF_DIGIT> to_sw;
  sc_in <bool> hw_enable; 
  sc_out <bool> hw_done;

  
  //Interconnection Signals
  
  sc_signal<NN_DIGIT> c_hh,c_lh,t0,t1,c,u1,v1;
  sc_signal<NN_HALF_DIGIT> aLow;
  sc_signal<NN_DIGIT> u2,v2;
  sc_signal<NN_DIGIT> t0_sub_u,t0_sub_vhh;
  sc_signal<NN_DIGIT> t1_submux_1,t1_submux_2,t1_submux_1out,t1_submux_2out;
  sc_signal<NN_DIGIT> t1_sub_vhh,vhh,vhh2;
  sc_signal<bool> ld_c,ld_t0,ld_t1,gt_1,gt_2,ld_aLow,t1_mux_1_ctrl, t1_mux_2_ctrl;
  sc_signal<UINT4> md1,const1;
  
  //Module initialize
  
  //Registers
  hw_register c_register, t0_register, t1_register;
  hw_register_h aLow_register;
  //Splitters
  hw_splitter c_splitter;
  //Multipliers
  hw_multiplier u_multiplier, v_multiplier;
  //Subtractors (subbers)
  hw_subber t0_subber_u,u_subber_MAX,t0_subber_vhh,vhh_subber_MAX,t1_subber_1,t1_subber_2,t1_subber_3;
  //Multiplexors
  hw_multiplexor t0_multiplexor_1, t0_multiplexor_2;
  //Comparators
  hw_comparator t0_comparator_1, t0_comparator_2;
  //Hardware TO High Half
  hw_to_hh v_to_hh;
  //Hardware High Half Extraction
  hw_hh_extract v_hh_extract;
  
  
  //LH divider function
  void process_hw();
  
  SC_CTOR (dh_hw):aLow_register("aLow_register"),c_register("c_register"),t0_register("t0_register"),t1_register("t1_register"),c_splitter("c_splitter"),u_multiplier("u_multiplier"),v_multiplier("v_multiplier"),t0_subber_u("t0_subber_u"),u_subber_MAX("u_subber_MAX"),t0_subber_vhh("t0_subber_vhh"),vhh_subber_MAX("vhh_subber_MAX"),t1_subber_1("t1_subber_1"),t1_subber_2("t1_subber_2"),t1_subber_3("t1_subber_3"),t0_multiplexor_1("t0_multiplexor_1"),t0_multiplexor_2("t0_multiplexor_2"),t0_comparator_1("t0_comparator_1"),t0_comparator_2("t0_comparator_2"),v_to_hh("v_to_hh"),v_hh_extract("v_hh_extract")
   {
   //
     
     //Constants
     md1.write(0xffffffff);
     const1.write(0x1);
     
     //Register Interconnections
     t0_register.clk(clk); t0_register.in_data(from_sw0);  t0_register.load_data(ld_t0); t0_register.out_data(t0);
     t1_register.clk(clk); t1_register.in_data(from_sw1);  t1_register.load_data(ld_t1); t1_register.out_data(t1);
     c_register.clk(clk); c_register.in_data(from_sw2); c_register.load_data(ld_c); c_register.out_data(c);
     aLow_register.clk(clk); aLow_register.in_data(from_sw3); aLow_register.load_data(ld_aLow); aLow_register.out_data(aLow);
     
     //Splitter Interconnections
     c_splitter.in_data(c); c_splitter.out_data_high(c_hh); c_splitter.out_data_low(c_lh); 
     
     
     //Multiplication Interconnections
     u_multiplier.in_data_1(aLow);u_multiplier.in_data_2(c_lh);u_multiplier.out_data(u1);
     v_multiplier.in_data_1(aLow);v_multiplier.in_data_2(c_hh);v_multiplier.out_data(v1);
     
     //Subber Interconnection
     t0_subber_u.in_data_1(t0);t0_subber_u.in_data_2(u1);t0_subber_u.out_data(t0_sub_u);
     u_subber_MAX.in_data_1(md1); u_subber_MAX.in_data_2(u1); u_subber_MAX.out_data(u2);
     t0_subber_vhh.in_data_1(t0_sub_u);t0_subber_vhh.in_data_2(vhh); t0_subber_vhh.out_data(t0_sub_vhh);
     vhh_subber_MAX.in_data_1(md1); vhh_subber_MAX.in_data_2(vhh); vhh_subber_MAX.out_data(v2);
     //Mux inputs
     t1_subber_1.in_data_1(t1); t1_subber_1.in_data_2(const1);t1_subber_1.out_data(t1_submux_1);
     
     t1_subber_2.in_data_1(t1_submux_1out); t1_subber_2.in_data_2(const1);t1_subber_2.out_data(t1_submux_2);
     
     t1_subber_3.in_data_1(t1_submux_2out); t1_subber_3.in_data_2(vhh2);t1_subber_3.out_data(t1_sub_vhh);
     
     
     //Mux Interconnections
     t0_multiplexor_1.in_data_1(t1);t0_multiplexor_1.in_data_2(t1_submux_1);t0_multiplexor_1.control(t1_mux_1_ctrl); t0_multiplexor_1.out_data(t1_submux_1out);
     t0_multiplexor_2.in_data_1(t1_submux_1out);t0_multiplexor_2.in_data_2(t1_submux_2);t0_multiplexor_2.control(t1_mux_2_ctrl); t0_multiplexor_2.out_data(t1_submux_2out);
     
     
     //GT Interconnections
     t0_comparator_1.in_data_reference(u2);t0_comparator_1.in_data_comparison(t0_sub_u);t0_comparator_1.greater_than_signal(gt_1);
     t0_comparator_2.in_data_reference(t0_sub_vhh);t0_comparator_2.in_data_comparison(v2);t0_comparator_2.greater_than_signal(gt_2);
     
     //HH interconnections
     v_to_hh.in_data(v1); v_to_hh.out_data(vhh);
     v_hh_extract.in_data(v1); v_hh_extract.out_data(vhh2);   
   //    
     //Divider thread
     SC_CTHREAD (process_hw, clk.pos());
  }
  
};

#endif /* end _DH_HW_H_ */
