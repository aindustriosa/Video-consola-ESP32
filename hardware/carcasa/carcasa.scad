// carcasa.scad - Carcasa da videoconsola ESP32 (PCB V2).
//
// Pezas (exportar cada unha a STL):
//   openscad -D 'parte="fronte"'   -o fronte.stl   carcasa.scad
//   openscad -D 'parte="traseira"' -o traseira.stl carcasa.scad
//   openscad -D 'parte="botons"'   -o botons.stl   carcasa.scad
//   parte="montaxe" amosa todo montado (coa PCB, a pantalla e a batería) para revisar.
//
// Sistema de coordenadas (mirando a consola de fronte, en mm):
//   x = desde o bordo esquerdo da PCB, y = desde o bordo inferior da PCB,
//   z = 0 na cara dianteira da PCB (a dos botóns), positivo cara a quen xoga.
// As posicións dos compoñentes saen do ficheiro KiCad da PCB V2.
//
// Montaxe: a PCB queda apertada entre os postes da fronte e os da traseira.
// 4 parafusos M3 x 25 desde atrás (cabeza avellanada) roscan nos postes da fronte.

parte = "montaxe";   // "fronte" | "traseira" | "botons" | "montaxe"
$fn = 48;

// ---------- PCB ----------
PCB_W = 60.05;
PCB_H = 90.05;
PCB_T = 1.6;
PCB_R = 5;

// ---------- Pantalla: módulo 2.4" ILI9341 (MSP2402) soldado directo ----------
MOD_W   = 42.72;
MOD_H   = 77.18;
MOD_X   = 6.65;          // bordo esquerdo do módulo (o pin T_IRQ queda a 4,85 do bordo dereito)
MOD_Y   = 39.67;         // bordo inferior do módulo (fila de pins a 2,00 del)
MOD_SEP = 2.5;           // separador de plástico dos pins
MOD_T   = 1.6;           // grosor da PCB do módulo
LCD_T   = 3.2;           // grosor do LCD (cristal + luz traseira)
CRISTAL_Y = MOD_Y + 10.41;
CRISTAL_H = 60.26;
VIS_W = 36.72;           // zona activa da imaxe
VIS_H = 48.96;
VIS_X = MOD_X + 3.0;
VIS_Y = CRISTAL_Y + CRISTAL_H - 2.95 - VIS_H;   // a zona activa vai cara á parte de arriba
VENTA_MARXE = 0.8;       // a ventá é un chisco máis grande que a imaxe
MOD_FURADOS = [[3.0, 6.92], [MOD_W - 3.0, 6.92], [3.0, MOD_H - 3.0], [MOD_W - 3.0, MOD_H - 3.0]];

// ---------- Botóns (pulsadores 6x6x5 mm na cara dianteira) ----------
BTN_ALTO = 5;            // altura do pulsador desde a PCB
CRUZ     = [13.8, 14.3]; // centro da cruceta (hai un furado de 6 mm na PCB)
BTN_A    = [50.84, 9.68];
BTN_B    = [39.98, 9.77];
BTN_MENU = [44.91, 20.94];

// ---------- Zumbador ----------
ZUMB    = [29.82, 28.57];
ZUMB_D  = 12.6;
ZUMB_ALTO = 9.0;

// ---------- XIAO ESP32-C3 (cara traseira) ----------
USB_Y   = 63.05;         // centro do USB-C, no lateral dereito
USB_Z   = -PCB_T - 2.6;  // centro en altura (debaixo da placa do XIAO)

// ---------- Batería LiPo 103450 (10 x 34 x 50 mm) ----------
BAT_X0 = 1.0;  BAT_X1 = 35.6;    // oco (deixa sitio ao XIAO, que empeza en x=36.9)
BAT_Y0 = 6.0;  BAT_Y1 = 61.0;    // 50 mm + cables
BAT_T  = 10.5;
HOLGURA_PATAS = 2.5;             // espazo para as patas soldadas detrás da PCB

// ---------- Carcasa ----------
HOLGURA = 0.4;           // entre a PCB e a parede
PAREDE  = 2.2;
FONDO_T = 2.0;           // grosor da tapa traseira
PANEL_T = 3.0;           // grosor da fronte
R_EXT   = 7;
Z_CRISTAL = MOD_SEP + MOD_T + LCD_T;          // 7.3
Z_PANEL   = Z_CRISTAL + 0.3;                  // cara interior da fronte
Z_FRONTE  = Z_PANEL + PANEL_T;                // cara exterior da fronte
Z_CORTE   = -PCB_T;                           // onde se xuntan as dúas metades
Z_FONDO   = Z_CORTE - HOLGURA_PATAS - BAT_T - FONDO_T;

// Oco interior: a PCB, máis o "queixo" de abaixo (parafusos) e a pantalla que sobresae por riba.
IN_X0 = -HOLGURA;
IN_X1 = PCB_W + HOLGURA;
IN_Y0 = -9;
IN_Y1 = MOD_Y + MOD_H + 0.6;
EXT_X0 = IN_X0 - PAREDE;  EXT_X1 = IN_X1 + PAREDE;
EXT_Y0 = IN_Y0 - PAREDE;  EXT_Y1 = IN_Y1 + PAREDE;

PARAFUSOS = [[10, -4.8], [PCB_W - 10, -4.8], [3.0, 104], [PCB_W - 3.0, 104]];
POSTE_D   = 6.4;
FURADO_ROSCA = 2.6;      // M3 roscando no plástico (4.2 se usas insertos de latón)

// Postes que apertan a PCB (por diante e por detrás), en sitios sen compoñentes.
APOIOS_FRONTE   = [[3.5, 3.5], [56.55, 3.0], [3.5, 86.5], [56.5, 86.5]];
APOIOS_TRASEIRA = [[3.0, 2.5], [58.0, 3.0], [3.0, 87.0], [58.3, 85.0], [45.0, 49.0], [15.0, 80.0]];

// ---------- Utilidades ----------
module rect_redondo(x0, y0, x1, y1, r, h) {
  hull() for (x = [x0 + r, x1 - r], y = [y0 + r, y1 - r]) translate([x, y, 0]) cylinder(r = r, h = h);
}

module caixa_exterior(z0, z1) {
  translate([0, 0, z0]) rect_redondo(EXT_X0, EXT_Y0, EXT_X1, EXT_Y1, R_EXT, z1 - z0);
}

module oco_interior(z0, z1) {
  translate([0, 0, z0]) rect_redondo(IN_X0, IN_Y0, IN_X1, IN_Y1, R_EXT - PAREDE, z1 - z0);
}

// Forma da cruceta (unha cruz) cun ancho e un largo dados
module cruz(ancho, largo, h) {
  translate([-largo / 2, -ancho / 2, 0]) cube([largo, ancho, h]);
  translate([-ancho / 2, -largo / 2, 0]) cube([ancho, largo, h]);
}

// ---------- FRONTE ----------
CRUZ_ANCHO = 8.6;  CRUZ_LARGO = 25;
A_D = 8.6;  MENU_D = 6.6;   // diámetro dos botóns que saen fóra
XOGO = 0.6;                  // folgura dos botóns nos seus furados

module fronte() {
  difference() {
    union() {
      difference() {
        caixa_exterior(Z_CORTE, Z_FRONTE);
        oco_interior(Z_CORTE - 1, Z_PANEL);
      }
      // postes dos parafusos
      for (p = PARAFUSOS) translate([p[0], p[1], Z_CORTE]) cylinder(d = POSTE_D, h = Z_PANEL - Z_CORTE);
      // postes que apertan a PCB
      for (p = APOIOS_FRONTE) translate([p[0], p[1], 0]) cylinder(d = 4, h = Z_PANEL);
      // postes que suxeitan o módulo da pantalla (cun pivote nos seus furados)
      for (f = MOD_FURADOS) translate([MOD_X + f[0], MOD_Y + f[1], 0]) {
        translate([0, 0, MOD_SEP + MOD_T]) cylinder(d = 5.5, h = Z_PANEL - MOD_SEP - MOD_T);
        translate([0, 0, MOD_SEP + MOD_T - 1.4]) cylinder(d = 2.4, h = 1.5);
      }
    }
    // furados dos parafusos
    for (p = PARAFUSOS) translate([p[0], p[1], Z_CORTE - 1]) cylinder(d = FURADO_ROSCA, h = Z_FRONTE - 1.2 - Z_CORTE + 1);
    // ventá da pantalla, co bordo en chafrán cara a fóra
    hull() {
      translate([VIS_X - VENTA_MARXE, VIS_Y - VENTA_MARXE, Z_PANEL - 1])
        cube([VIS_W + 2 * VENTA_MARXE, VIS_H + 2 * VENTA_MARXE, 1.01]);
      translate([VIS_X - VENTA_MARXE - PANEL_T, VIS_Y - VENTA_MARXE - PANEL_T, Z_FRONTE])
        cube([VIS_W + 2 * (VENTA_MARXE + PANEL_T), VIS_H + 2 * (VENTA_MARXE + PANEL_T), 0.01]);
    }
    // oco para o cristal (por se o LCD é un pouco máis groso)
    translate([MOD_X - 0.3, CRISTAL_Y - 0.3, Z_PANEL - 0.6]) cube([MOD_W + 0.6, CRISTAL_H + 0.6, 0.61]);
    // botóns
    translate([CRUZ[0], CRUZ[1], 0]) cruz(CRUZ_ANCHO + XOGO, CRUZ_LARGO + XOGO, 50);
    for (b = [BTN_A, BTN_B]) translate([b[0], b[1], 0]) cylinder(d = A_D + XOGO, h = 50);
    translate([BTN_MENU[0], BTN_MENU[1], 0]) cylinder(d = MENU_D + XOGO, h = 50);
    // zumbador: oco por dentro e reixa de furadiños
    translate([ZUMB[0], ZUMB[1], 0]) cylinder(d = ZUMB_D + 1, h = ZUMB_ALTO + 0.3);
    for (dx = [-4.5 : 3 : 4.5], dy = [-4.5 : 3 : 4.5])
      if (dx * dx + dy * dy < 30) translate([ZUMB[0] + dx, ZUMB[1] + dy, 0]) cylinder(d = 1.6, h = 50);
    // letras gravadas
    translate([0, 0, Z_FRONTE - 0.6]) linear_extrude(1) {
      translate([BTN_A[0], BTN_A[1] - 9.8]) text("A", size = 3.5, halign = "center", font = "Liberation Sans:style=Bold");
      translate([BTN_B[0], BTN_B[1] - 9.8]) text("B", size = 3.5, halign = "center", font = "Liberation Sans:style=Bold");
      translate([BTN_MENU[0], BTN_MENU[1] + 5.4]) text("MENU", size = 2.6, halign = "center", font = "Liberation Sans:style=Bold");
    }
  }
}

// ---------- TRASEIRA ----------
module traseira() {
  difference() {
    union() {
      difference() {
        caixa_exterior(Z_FONDO, Z_CORTE);
        oco_interior(Z_FONDO + FONDO_T, Z_CORTE + 1);
      }
      // postes dos parafusos
      for (p = PARAFUSOS) translate([p[0], p[1], Z_FONDO]) cylinder(d = POSTE_D, h = Z_CORTE - Z_FONDO);
      // postes que apertan a PCB por detrás
      for (p = APOIOS_TRASEIRA) translate([p[0], p[1], Z_FONDO]) cylinder(d = 3, h = Z_CORTE - Z_FONDO);
      // muros baixos que suxeitan a batería
      translate([0, 0, Z_FONDO]) difference() {
        translate([BAT_X0 - 1, BAT_Y0 - 1, 0]) cube([BAT_X1 - BAT_X0 + 2, BAT_Y1 - BAT_Y0 + 2, FONDO_T + BAT_T / 2]);
        translate([BAT_X0, BAT_Y0, -1]) cube([BAT_X1 - BAT_X0, BAT_Y1 - BAT_Y0, 50]);
        translate([BAT_X0 + 8, BAT_Y1 - 2, FONDO_T]) cube([BAT_X1 - BAT_X0 - 16, 5, 50]);   // saída dos cables
      }
    }
    // furados dos parafusos, avellanados por fóra
    for (p = PARAFUSOS) translate([p[0], p[1], Z_FONDO - 1]) {
      cylinder(d = 3.4, h = 50);
      cylinder(d1 = 7.4, d2 = 3.4, h = 1 + 2);
    }
    // USB-C no lateral dereito
    translate([IN_X1 - 1, USB_Y, USB_Z]) rotate([0, 90, 0]) hull()
      for (d = [-3.2, 3.2]) translate([0, d, 0]) cylinder(d = 4.6, h = PAREDE + 2);
  }
}

// ---------- BOTÓNS (imprimir aparte, coa cara de arriba cara abaixo) ----------
Z_ABA = Z_PANEL - 0.2;      // o "ala" que evita que o botón saia queda xusto baixo a fronte
Z_TOPO = Z_FRONTE + 1.5;    // canto sobresaen

module boton_cruz() {
  translate([CRUZ[0], CRUZ[1], 0]) {
    translate([0, 0, BTN_ALTO]) cruz(11, CRUZ_LARGO + 1.6, Z_ABA - BTN_ALTO);
    translate([0, 0, Z_ABA]) cruz(CRUZ_ANCHO, CRUZ_LARGO, Z_TOPO - Z_ABA);
    // pivote central: apoia na PCB e entra no furado de 6 mm
    cylinder(d = 7, h = BTN_ALTO);
    translate([0, 0, -1.2]) cylinder(d = 4.5, h = 1.3);
  }
}

module boton_redondo(p, d, aba) {
  translate([p[0], p[1], 0]) {
    translate([0, 0, BTN_ALTO]) cylinder(d = aba, h = Z_ABA - BTN_ALTO);
    translate([0, 0, Z_ABA]) cylinder(d = d, h = Z_TOPO - Z_ABA);
  }
}

module botons_montados() {
  boton_cruz();
  boton_redondo(BTN_A, A_D, 10.6);
  boton_redondo(BTN_B, A_D, 10.6);
  boton_redondo(BTN_MENU, MENU_D, 9);
}

// Para imprimir: dados a volta e apoiados na cama
module botons_para_imprimir() {
  translate([0, 0, Z_TOPO]) rotate([180, 0, 0]) {
    translate([-CRUZ[0], -CRUZ[1], 0]) boton_cruz();
    translate([22 - BTN_A[0], -BTN_A[1], 0]) boton_redondo(BTN_A, A_D, 10.6);
    translate([36 - BTN_B[0], -BTN_B[1], 0]) boton_redondo(BTN_B, A_D, 10.6);
    translate([48 - BTN_MENU[0], -BTN_MENU[1], 0]) boton_redondo(BTN_MENU, MENU_D, 9);
  }
}

// ---------- Maqueta das pezas electrónicas (só para revisar a montaxe) ----------
module electronica() {
  color("green") translate([0, 0, -PCB_T]) rect_redondo(0, 0, PCB_W, PCB_H, PCB_R, PCB_T);
  color("red") translate([MOD_X, MOD_Y, MOD_SEP]) cube([MOD_W, MOD_H, MOD_T]);
  color("black") translate([MOD_X, CRISTAL_Y, MOD_SEP + MOD_T]) cube([MOD_W, CRISTAL_H, LCD_T]);
  color("white") translate([VIS_X, VIS_Y, Z_CRISTAL]) cube([VIS_W, VIS_H, 0.05]);
  color("gray") for (b = [[13.88, 22.98], [13.81, 5.33], [4.81, 14.33], [22.89, 14.3], BTN_A, BTN_B, BTN_MENU])
    translate([b[0] - 3, b[1] - 3, 0]) cube([6, 6, BTN_ALTO]);
  color("black") translate([ZUMB[0], ZUMB[1], 0]) cylinder(d = ZUMB_D, h = ZUMB_ALTO);
  color("silver") translate([38.5, 54, -PCB_T - 4.2]) cube([21.5, 17.8, 4.2]);   // XIAO
  color("blue") translate([BAT_X0 + 0.3, BAT_Y0 + 0.5, Z_FONDO + FONDO_T]) cube([34, 50, 10]);
}

if (parte == "fronte") fronte();
else if (parte == "traseira") traseira();
else if (parte == "botons") botons_para_imprimir();
else if (parte == "montaxe") {
  electronica();
  botons_montados();
  color("orange", 0.35) fronte();
  color("lightblue", 0.5) traseira();
}
