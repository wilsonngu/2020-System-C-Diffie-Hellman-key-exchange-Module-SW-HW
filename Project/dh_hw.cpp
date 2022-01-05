#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"
#include "modules.h"

#define WAIT_STATE 0
#define INPUT_STATE 1
#define EXECUTE_STATE 2
#define OUTPUT_STATE 3
#define FINISH_STATE 4

void dh_hw::process_hw()
{

  //Initialize values
  UINT2 current_state = WAIT_STATE;
//  NN_DIGIT t[2], c, u, v;
//  NN_HALF_DIGIT aLow, cLow, cHigh;  
      // Signal HW computation begins
       hw_done.write(false);
        while (true)
       { 
      
          switch(current_state)
          {
        
              case WAIT_STATE:
    	    	//wait for SW to initiate the multiplication
               // cout << "HW enable VALUE IS:" << hw_enable << " WAIT STATE!\n";
        
                if (hw_enable.read() == true)
                {
                  //cout << "going to EXECUTE STATE!\n";
    		          current_state = EXECUTE_STATE;
                }
                break;
              case INPUT_STATE:
                  //READ INPUTS
                  ld_c.write(1);
                  ld_t0.write(1);
                  ld_t1.write(1);
                  ld_aLow.write(1);
                  t1_mux_1_ctrl.write(0);
                  t1_mux_2_ctrl.write(0);
                  //
                  current_state = EXECUTE_STATE;
         
                  break;  
                            
              case EXECUTE_STATE:              
                  //EXECUTE       
                  //update values from calculated values
                  //ld_t0.write(0);
                  t1_mux_1_ctrl.write(gt_1.read());
                  //ld_t0.write(1);
                  //ld_t0.write(0);
                  t1_mux_2_ctrl.write(gt_2.read());
                  current_state = OUTPUT_STATE;
                 // cout << "Hardware is done computed\n";            
                  break;    
               case OUTPUT_STATE:   
                  //Output for datapath
                  to_sw.write(aLow.read());
                  hw_done.write(true);
                  current_state = FINISH_STATE;
                  //
               break;    
             
              case FINISH_STATE:
               if (hw_enable.read() == false)
                 {
                 //Wait for notification from software that division is complete, repeat
                  hw_done.write(false);
                  current_state = WAIT_STATE;
                 }
                 break;               
            }
                    
         //Wait for next clock cycle
            wait();
    	      wait();
                 
        } 

 	  
}

