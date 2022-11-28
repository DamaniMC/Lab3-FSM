#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"
#include "vbuddy.cpp"

#define MAX_SIM_CYC 1000000 
int main(int argc, char **argv, char **env) {
    int i; // simulation clock count
    int clk;

    Verilated::commandArgs(argc, argv);
    Vf1_fsm* top=new Vf1_fsm;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp=new VerilatedVcdC;

    top->trace(tfp, 99);
    tfp->open("f1_fsm.vcd");

    if(vbdOpen() !=1) return(-1);
    vbdHeader("Lab 3: FSM");

    vbdSetMode(1);
    top->clk=1;
    top->rst=1;
    top->en=1;
   

    for (i=0; i<MAX_SIM_CYC; i++) {
        for (clk=0; clk < 2; clk++) {
            tfp->dump (2*i+clk);
            top->clk= !top->clk;
            top->eval ();
        }
        top->rst=(i<2);
      
        vbdHex(4, ((top->out)>>16)& 0xF);
        vbdHex(3, ((top->out)>>8)& 0xF);
        vbdHex(2, ((top->out)>>4)& 0xF);
        vbdHex(1, ((top->out))& 0xF);
        vbdBar(top->out & 0xFF);
        vbdCycle(i+1);
        top->en=vbdFlag();
        if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);  
    }

    vbdClose();
    tfp->close();
    exit(0);
}