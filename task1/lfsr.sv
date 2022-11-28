module lsfr(
    input logic rst,
    input logic en,
    input logic clk,
    output logic [4:1] data_out
);

logic [4:1] sreg;

always_ff @(posedge clk,posedge rst) begin
    if(rst)
        sreg <= 4'b1;
    else if (en)begin
    sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};
    data_out<=sreg;
    end
end
endmodule