--------------------------------------------------------------------------------
-- Procesador MIPS con pipeline curso Arquitectura 2020-2021
--
-- Pablo Almarza y Jorge González
--
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity processor is
   port(
      Clk         : in  std_logic; -- Reloj activo en flanco subida
      Reset       : in  std_logic; -- Reset asincrono activo nivel alto
      -- Instruction memory
      IAddr      : out std_logic_vector(31 downto 0); -- Direccion Instr
      IDataIn    : in  std_logic_vector(31 downto 0); -- Instruccion leida
      -- Data memory
      DAddr      : out std_logic_vector(31 downto 0); -- Direccion
      DRdEn      : out std_logic;                     -- Habilitacion lectura
      DWrEn      : out std_logic;                     -- Habilitacion escritura
      DDataOut   : out std_logic_vector(31 downto 0); -- Dato escrito
      DDataIn    : in  std_logic_vector(31 downto 0)  -- Dato leido
   );
end processor;

architecture rtl of processor is

  component alu
    port(
      OpA : in std_logic_vector (31 downto 0);
      OpB : in std_logic_vector (31 downto 0);
      Control : in std_logic_vector (3 downto 0);
      Result : out std_logic_vector (31 downto 0);
      Zflag : out std_logic
    );
  end component;

  component reg_bank
     port (
        Clk   : in std_logic; -- Reloj activo en flanco de subida
        Reset : in std_logic; -- Reset as�ncrono a nivel alto
        A1    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd1
        Rd1   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd1
        A2    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Rd2
        Rd2   : out std_logic_vector(31 downto 0); -- Dato del puerto Rd2
        A3    : in std_logic_vector(4 downto 0);   -- Direcci�n para el puerto Wd3
        Wd3   : in std_logic_vector(31 downto 0);  -- Dato de entrada Wd3
        We3   : in std_logic -- Habilitaci�n de la escritura de Wd3
     );
  end component reg_bank;

  component control_unit
     port (
        -- Entrada = codigo de operacion en la instruccion:
        OpCode   : in  std_logic_vector (5 downto 0);
        IsNop    : in std_logic;
        -- Seniales para el PC
        Jump     : out std_logic; -- 1 = Ejecutandose instruccion jump
        Branch   : out  std_logic; -- 1 = Ejecutandose instruccion branch
        -- Seniales relativas a la memoria
        MemToReg : out  std_logic; -- 1 = Escribir en registro la salida de la mem.
        MemWrite : out  std_logic; -- Escribir la memoria
        MemRead  : out  std_logic; -- Leer la memoria
        -- Seniales para la ALU
        ALUSrc   : out  std_logic;                     -- 0 = oper.B es registro, 1 = es valor inm.
        ALUOp    : out  std_logic_vector (2 downto 0); -- Tipo operacion para control de la ALU
        -- Seniales para el GPR
        RegWrite : out  std_logic; -- 1=Escribir registro
        RegDst   : out  std_logic  -- 0=Reg. destino es rt, 1=rd
     );
  end component;

  component alu_control is
   port (
      -- Entradas:
      ALUOp  : in std_logic_vector (2 downto 0); -- Codigo de control desde la unidad de control
      Funct  : in std_logic_vector (5 downto 0); -- Campo "funct" de la instruccion
      -- Salida de control para la ALU:
      ALUControl : out std_logic_vector (3 downto 0) -- Define operacion a ejecutar por la ALU
   );
 end component alu_control;

  signal Alu_Op2      : std_logic_vector(31 downto 0);
  signal AluControl   : std_logic_vector(3 downto 0);
  -- signal reg_RD_data  : std_logic_vector(31 downto 0);
  -- signal reg_RD       : std_logic_vector(4 downto 0);

  --signal Regs_eq_branch : std_logic;
  signal enable_PCwrite : std_logic;
  signal PC_next        : std_logic_vector(31 downto 0);
  signal PC_reg         : std_logic_vector(31 downto 0);
  signal PC_plus4       : std_logic_vector(31 downto 0);

  signal Instruction    : std_logic_vector(31 downto 0); -- La instrucción desde lamem de instr
  signal Inm_ext        : std_logic_vector(31 downto 0); --Lparte baja de la instrucción extendida de signo
  signal rd_RS, rd_RT : std_logic_vector(31 downto 0);

  -- signal Addr_Branch    : std_logic_vector(31 downto 0);

  signal Ctrl_Jump, Ctrl_Branch, Ctrl_MemWrite, Ctrl_MemRead,  Ctrl_ALUSrc, Ctrl_RegDest, Ctrl_MemToReg, Ctrl_RegWrite : std_logic;
  signal Ctrl_ALUOP     : std_logic_vector(2 downto 0);
  signal Ctrl_Zflag     : std_logic;

  --signal Addr_Jump      : std_logic_vector(31 downto 0);
  --signal Addr_Jump_dest : std_logic_vector(31 downto 0);
  signal Alu_Res        : std_logic_vector(31 downto 0);
  
  --Fetch process
  signal pcplus4_ID		  : std_logic_vector(31 downto 0);
  signal instruction_ID : std_logic_vector(31 downto 0);
  signal IsNop_AUX : std_logic;
  signal enable_IF_ID   : std_logic;
  
  --Decode process
  signal enable_ID_EX   : std_logic;
  signal pcplus4_EX		  : std_logic_vector(31 downto 0);
  signal reg_RS_EX      : std_logic_vector(4 downto 0);
  signal rd_RS_EX       : std_logic_vector(31 downto 0);
  signal reg_RD_EX      : std_logic_vector(4 downto 0);
  signal reg_RT_EX      : std_logic_vector(4 downto 0);
  signal rd_RT_EX       : std_logic_vector(31 downto 0);
  signal Branch_EX, MemtoReg_EX, MemWrite_EX, MemRead_EX, ALUSrc_EX, RegWrite_EX,  RegDst_EX   : std_logic;
  signal ALUOP_EX       : std_logic_vector(2 downto 0);
  signal Inm_Ext_EX     : std_logic_vector(31 downto 0);

  --Execute process
  signal branch_address_MEM, rd_RT_MEM    : std_logic_vector(31 downto 0);
  signal reg_Wd3_MEM, reg_Wd3_AUX         : std_logic_vector(4 downto 0);
  signal RegWrite_MEM, MemWrite_MEM, MemtoReg_MEM, MemRead_MEM, Zflag_MEM, Branch_MEM : std_logic;
  signal Alu_Res_MEM                      : std_logic_vector(31 downto 0);

  --Memory process
  signal Alu_Res_WB     : std_logic_vector(31 downto 0);
  signal RegWrite_WB, MemToReg_WB : std_logic;
  signal DataIn_WB      : std_logic_vector(31 downto 0);
  signal reg_Wd3_WB     : std_logic_vector(4 downto 0);
  signal Wd3_AUX        : std_logic_vector(31 downto 0);

  --Forwarding unit 
  signal ForwardA       : std_logic_vector(1 downto 0);
  signal ForwardB       : std_logic_vector(1 downto 0);
  signal ForwardAluOp1, ForwardAluOp2  : std_logic_vector(31 downto 0);

  --Hazard detection unit
  signal hazard_zero       : std_logic;

  -- Branch control hazard
  signal effective_branch  : std_logic;

  begin
  PC_plus4    <= PC_reg + 4;
  IAddr       <= PC_reg;
  Instruction <= IDataIn;

  -- We didn't feel like we needed another signal
  -- We just kept the code to have the base around in case we need it.
  -- Addr_Jump_dest <= Addr_Jump   when Ctrl_Jump='1' else
  --                   Addr_Branch when Ctrl_Branch='1' else
  --                   (others =>'0');
  
  -- Branch control hazard
  effective_branch <= (Branch_MEM and Zflag_MEM);

  PC_next <= pcplus4_ID(31 downto 28) & Instruction_ID(25 downto 0) & "00" when Ctrl_Jump = '1'
             else branch_address_MEM when (Branch_MEM and Zflag_MEM) = '1' else PC_plus4;
  
  -- Data forwarding unit
  Data_Forwarding: process(RegWrite_MEM, reg_Wd3_MEM, reg_RS_EX, reg_RT_EX, -- EX hazard
                           RegWrite_WB,  reg_Wd3_WB)                        -- MEM hazard
  begin
        
    -- EX hazard
    if RegWrite_MEM = '1' and reg_Wd3_MEM /= "00000" then
      if reg_Wd3_MEM = reg_RS_EX then
        ForwardA <= "10";
      end if;
      if reg_Wd3_MEM = reg_RT_EX then
        ForwardB <= "10";
      end if;

    -- MEM hazard
    elsif RegWrite_WB = '1' and reg_Wd3_WB /= "00000" then
      if reg_Wd3_WB = reg_RS_EX then
        ForwardA <= "01";
      end if;
      if reg_Wd3_WB = reg_RT_EX then
        ForwardB <= "01";
      end if;

    -- No hazard
    else 
      ForwardA <= "00";
      ForwardB <= "00";
    end if;

  end process;


  Hazard_detection_unit: process(reg_RT_EX, Instruction_ID, MemRead_EX)
  begin
    -- reg_RS_EX <= Instruction_ID(25 downto 21);
    -- reg_RT_EX <= Instruction_ID(20 downto 16);
    if (Instruction_ID(25 downto 21) = reg_RT_EX or 
        Instruction_ID(20 downto 16) = reg_RT_EX) and
       reg_RT_EX /= "00000" and
       MEMRead_EX = '1' then
        enable_PCWrite <= '0';
        enable_IF_ID <= '0';
        hazard_zero <= '1';
    else
        hazard_zero <= '0';
        enable_PCWrite <= '1';
        enable_IF_ID <= '1';
    end if;

  end process;

  PC_reg_proc: process(Clk, Reset, enable_PCwrite)
  begin
    if Reset = '1' then
      PC_reg <= (others => '0');
    elsif rising_edge(Clk) and enable_PCwrite = '1' then
      PC_reg <= PC_next;
    end if;
  end process;

  InsFetch_to_InsDecode: process(Clk, Reset, enable_IF_ID)
    begin
    if Reset = '1' or (effective_branch = '1' and rising_edge(Clk)) then
      pcplus4_ID <= (others => '0');
      instruction_ID <= (others => '0');
    elsif rising_edge(Clk) and enable_IF_ID = '1' then 
      pcplus4_ID <= PC_plus4;
      instruction_ID <= Instruction;
    end if;
  end process;
	
  InsDecode_to_Execute: process (Clk, Reset, hazard_zero)
  begin 
	if Reset = '1' or (effective_branch = '1' and rising_edge(Clk)) then 
		pcplus4_EX <= (others => '0');
    rd_RS_EX <= (others => '0');
		rd_RT_EX <= (others => '0');
		reg_RD_EX <= (others => '0');
		Branch_EX <= '0';
		MemtoReg_EX <= '0';
		MemWrite_EX <= '0';
		MemRead_EX <= '0';
		ALUSrc_EX <= '0';
		ALUOP_EX <= (others => '0');
		RegWrite_EX <= '0';
    RegDst_EX <= '0';
    reg_RT_EX <= (others => '0');
    Inm_Ext_EX <= (others => '0');
    reg_RS_EX <= (others => '0');
  elsif rising_edge(Clk) and enable_ID_EX = '1' then
    rd_RS_EX <= rd_RS;
    rd_RT_EX <= rd_RT;
    pcplus4_EX <= pcplus4_ID;
    reg_RS_EX <= Instruction_ID(25 downto 21);
    reg_RT_EX <= Instruction_ID(20 downto 16);
    reg_RD_EX <= Instruction_ID(15 downto 11);
    Inm_Ext_EX <= Inm_Ext;
    -- In-process multiplexer for Data Hazard
    if hazard_zero = '1' then
      Branch_EX <= '0';
      MemtoReg_EX <= '0';
      MemRead_EX <= '0';
      ALUSrc_EX <= '0';
      ALUOP_EX <= (others => '0');
      RegDst_EX <= '0';
      MemWrite_EX <= '0';
      RegWrite_EX <= '0';
    else
      Branch_EX <= Ctrl_Branch;
      MemtoReg_EX <= Ctrl_MemToReg;
      MemRead_EX <= Ctrl_MemRead;
      ALUSrc_EX <= Ctrl_ALUSrc;
      ALUOP_EX <= Ctrl_ALUOP;
      RegDst_EX <= Ctrl_RegDest;
      MemWrite_EX <= Ctrl_MemWrite;
      RegWrite_EX <= Ctrl_RegWrite;
    end if;
	end if;
  end process;

  with Instruction_ID(15) select
    Inm_Ext <= x"FFFF" & Instruction_ID(15 downto 0) when '1',
                  x"0000" & Instruction_ID(15 downto 0) when others;

  enable_ID_EX <= '1';

  Execute_to_Memory: process (Clk, Reset)
  begin
  if Reset = '1' then
    branch_address_MEM <= (others => '0');
    RegWrite_MEM <= '0';
    MemWrite_MEM <= '0';
    MemRead_MEM <= '0';
    MemtoReg_MEM <= '0';
    Alu_Res_MEM <= (others => '0');
    reg_Wd3_MEM <= (others => '0');
    rd_RT_MEM <= (others => '0');
    Zflag_MEM <= '0';
    Branch_MEM <= '0';
  elsif rising_edge(Clk) then
    branch_address_MEM <= pcplus4_EX + (Inm_Ext_EX(29 downto 0) & "00");
    RegWrite_MEM <= RegWrite_EX;
    MemWrite_MEM <= MemWrite_EX;
    MemRead_MEM <= MemRead_EX;
    Alu_Res_MEM <= Alu_Res;
    MemtoReg_MEM <= MemToReg_EX;
    rd_RT_MEM <= rd_RT_EX;
    reg_Wd3_MEM <= reg_Wd3_AUX;
    Zflag_MEM <= Ctrl_Zflag;
    Branch_MEM <= Branch_EX;
  end if;
  end process;
  
  -- Multiplexer to decide where the memory will be written 
  with RegDst_EX select
     reg_Wd3_AUX <= reg_RT_EX when '0', 
                    reg_RD_EX when others;

  Memory_to_WriteBack: process (Clk, Reset)
  begin
  if Reset = '1' then 
    RegWrite_WB <= '0';
    Alu_Res_WB <= (others => '0');
    Reg_Wd3_WB <= (others => '0');
    MemToReg_WB <= '0';
    DataIn_WB <= (others => '0');
  elsif rising_edge(Clk) then 
    RegWrite_WB <= RegWrite_MEM;
    Alu_Res_WB <= Alu_Res_MEM;
    DataIn_WB <= DDataIn;
    reg_Wd3_WB <= reg_Wd3_MEM;
    MemToReg_WB <= MemToReg_MEM;
  end if;
  end process;

  -- Last multiplexer to decide what goes into the memory
  with MemToReg_WB select
    Wd3_AUX <= DataIn_WB when '1',
    Alu_Res_WB when others;
  
  RegsMIPS : reg_bank
  port map (
    Clk   => Clk,
    Reset => Reset,
    A1    => instruction_ID(25 downto 21),
    Rd1   => rd_RS,
    A2    => instruction_ID(20 downto 16),
    Rd2   => rd_RT,
    A3    => reg_Wd3_WB,
    Wd3   => Wd3_AUX,
    We3   => RegWrite_WB
  );

  IsNop_AUX <= '1' when Instruction_ID = X"00000000" else '0';

  UnidadControl : control_unit
  port map(
    OpCode   => instruction_ID(31 downto 26),
    IsNop => IsNop_AUX,
    -- Señales para el PC
    Jump   => Ctrl_Jump,
    Branch   => Ctrl_Branch,
    -- Señales para la memoria
    MemToReg => Ctrl_MemToReg,
    MemWrite => Ctrl_MemWrite,
    MemRead  => Ctrl_MemRead,
    -- Señales para la ALU
    ALUSrc   => Ctrl_ALUSrc,
    ALUOP    => Ctrl_ALUOP,
    -- Señales para el GPR
    RegWrite => Ctrl_RegWrite,
    RegDst   => Ctrl_RegDest
  );

  Alu_control_i: alu_control
  port map(
    -- Entradas:
    ALUOp  => ALUOP_EX, -- Codigo de control desde la unidad de control
    Funct  => Inm_Ext_EX(5 downto 0), -- Campo "funct" de la instruccion
    -- Salida de control para la ALU:
    ALUControl => AluControl -- Define operacion a ejecutar por la ALU
  );

  Alu_MIPS : alu
  port map (
    OpA     => ForwardAluOp1,
    OpB     => Alu_Op2,
    Control => AluControl,
    Result  => Alu_Res,
    Zflag   => Ctrl_Zflag
  );
  
  -- Multiplexer using ForwardA
  with ForwardA select
    ForwardAluOp1 <= rd_RS_EX when "00",
                     Wd3_AUX when "01",
                     Alu_Res_MEM when others;
  
  -- Multiplexer using ForwardB
  with ForwardB select
    ForwardAluOp2 <= rd_RT_EX when "00",
                      Wd3_AUX when "01",
                      Alu_Res_MEM when others;                
  
  with ALUSrc_EX select
    Alu_Op2    <= ForwardAluOp2 when '0', 
                  Inm_ext_EX when others;

  DAddr      <= Alu_Res_MEM;
  DWrEn      <= MemWrite_MEM;
  DRdEn      <= MemRead_MEM;
  DDataOut   <= rd_RT_MEM;

end architecture;
