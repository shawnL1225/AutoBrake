package example;

import java.awt.Button;
import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.List;
import java.awt.Panel;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
//import java.util.TimerTask;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JSlider;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.fazecast.jSerialComm.SerialPort;
import java.awt.TextArea;
import javax.swing.JTextPane;


public class first {

  static JFrame frame;
  
  static JLabel Mother_Board_ConditionLight;
  static JLabel NXT_ConditionLight;
  static JLabel CTRL_Board_ConditionLight;
  static JLabel Brake_F_ConditionLight;
  static JLabel Brake_B_ConditionLight;
  static JLabel Distance_F_ConditionLight;
  static JLabel Distance_L_ConditionLight;
  static JLabel Distance_R_ConditionLight;
  static JLabel Distance_B_ConditionLight;
  static JLabel Speed_Sensor_ConditionLight;
  static JLabel Voltage_n_heat_ConditionLight;
  
  static JLabel Motor_Temp_V;
  static JLabel Vichele_Tilt_Angle_V;
  static JLabel Vichele_Speed_V;
  static JLabel Actual_motor_percentage_V;
  static JLabel Controller_Perentage_V;
  static JLabel Battery_Percentage_V;
  static JLabel Front_Brake_V;
  static JLabel Back_Brake_V;
  
  static JSlider Actual_Motor_Percentage_Control_Slider;
  static JSlider Front_Brake_Slider;
  static JSlider Back_Brake_Slider;
  
  static List Mother_Board_Serial_List;
  static List NXT_Serial_List;
  
  static JComboBox<String> COM_selection_comboBox;
  
  static JButton Disable_or_enable_the_motor_Button;
  
  static SerialPort chosenPort;
  static boolean hasChoosePort =false;
  static Timer timer;
  

  
  
  @SuppressWarnings("deprecation")
  public static void main(String[] args) {
    timer = new Timer();
    timer.scheduleAtFixedRate(new RemindTask(),0, 1);
    frame = new JFrame();
    frame.setIconImage(Toolkit.getDefaultToolkit().getImage("D:\\AutoBrake_ComputerSite_System\\image\\MSBA_icon.png"));
    frame.getContentPane().setBackground(Color.WHITE);
    frame.setBounds(100, 100, 450, 300);
    frame.setExtendedState(JFrame.MAXIMIZED_BOTH); 
    frame.setSize(1650,1080);
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.getContentPane().setLayout(null);
    
    JScrollPane scrollPane = new JScrollPane(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    scrollPane.setBounds(10, 0, 195, 204);
    frame.getContentPane().add(scrollPane);
    
    Box verticalBox_1 = Box.createVerticalBox();
    scrollPane.setViewportView(verticalBox_1);
    
    Panel Mother_Board_Panel = new Panel();
    verticalBox_1.add(Mother_Board_Panel);
    
    Panel NXT_Panel = new Panel();
    verticalBox_1.add(NXT_Panel);
    
    Panel CTRL_Board_Panel = new Panel();
    verticalBox_1.add(CTRL_Board_Panel);
    
    Panel Brake_F_Panel = new Panel();
    verticalBox_1.add(Brake_F_Panel);
    
    Panel Brake_B_Panel = new Panel();
    verticalBox_1.add(Brake_B_Panel);
    
    Panel Distance_F_Panel = new Panel();
    verticalBox_1.add(Distance_F_Panel);
    
    Panel Distance_L_Panel = new Panel();
    verticalBox_1.add(Distance_L_Panel);
    
    Panel Distance_R_Panel = new Panel();
    verticalBox_1.add(Distance_R_Panel);
    
    Panel Distance_B_Panel = new Panel();
    verticalBox_1.add(Distance_B_Panel);
    
    Panel Speed_Sensor_Panel = new Panel();
    verticalBox_1.add(Speed_Sensor_Panel);
    
    Panel Voltage_n_heat_Panel = new Panel();
    verticalBox_1.add(Voltage_n_heat_Panel);
    
    Mother_Board_ConditionLight = new JLabel("\u25CF");
    Mother_Board_ConditionLight.setToolTipText("disconnect");
    Mother_Board_Panel.add(Mother_Board_ConditionLight);
    Mother_Board_ConditionLight.setAlignmentY(Component.TOP_ALIGNMENT);
    Mother_Board_ConditionLight.setForeground(Color.RED);
    Mother_Board_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    NXT_ConditionLight = new JLabel("\u25CF");
    NXT_ConditionLight.setToolTipText("disconnect");
    NXT_Panel.add(NXT_ConditionLight);
    NXT_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    NXT_ConditionLight.setForeground(Color.RED);

    CTRL_Board_ConditionLight = new JLabel("\u25CF");
    CTRL_Board_ConditionLight.setToolTipText("disconnect");
    CTRL_Board_Panel.add(CTRL_Board_ConditionLight);
    CTRL_Board_ConditionLight.setForeground(Color.RED);
    CTRL_Board_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    Brake_F_ConditionLight = new JLabel("\u25CF");
    Brake_F_ConditionLight.setToolTipText("disconnect");
    Brake_F_ConditionLight.setForeground(Color.RED);
    Brake_F_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    Brake_F_Panel.add(Brake_F_ConditionLight);

    Brake_B_ConditionLight = new JLabel("\u25CF");
    Brake_B_ConditionLight.setToolTipText("disconnect");
    Brake_B_ConditionLight.setForeground(Color.RED);
    Brake_B_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    Brake_B_Panel.add(Brake_B_ConditionLight);

    Distance_F_ConditionLight = new JLabel("\u25CF");
    Distance_F_ConditionLight.setToolTipText("disconnect");
    Distance_F_Panel.add(Distance_F_ConditionLight);
    Distance_F_ConditionLight.setForeground(Color.RED);
    Distance_F_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    Distance_L_ConditionLight = new JLabel("\u25CF");
    Distance_L_ConditionLight.setToolTipText("disconnect");
    Distance_L_Panel.add(Distance_L_ConditionLight);
    Distance_L_ConditionLight.setForeground(Color.RED);
    Distance_L_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    Distance_R_ConditionLight = new JLabel("\u25CF");
    Distance_R_ConditionLight.setToolTipText("disconnect");
    Distance_R_Panel.add(Distance_R_ConditionLight);
    Distance_R_ConditionLight.setForeground(Color.RED);
    Distance_R_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    Distance_B_ConditionLight = new JLabel("\u25CF");
    Distance_B_ConditionLight.setToolTipText("disconnect");
    Distance_B_Panel.add(Distance_B_ConditionLight);
    Distance_B_ConditionLight.setForeground(Color.RED);
    Distance_B_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));

    Speed_Sensor_ConditionLight = new JLabel("\u25CF");
    Speed_Sensor_ConditionLight.setToolTipText("disconnect");
    Speed_Sensor_ConditionLight.setForeground(Color.RED);
    Speed_Sensor_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    Speed_Sensor_Panel.add(Speed_Sensor_ConditionLight);

    Voltage_n_heat_ConditionLight = new JLabel("\u25CF");
    Voltage_n_heat_ConditionLight.setToolTipText("disconnect");
    Voltage_n_heat_ConditionLight.setForeground(Color.RED);
    Voltage_n_heat_ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    Voltage_n_heat_Panel.add(Voltage_n_heat_ConditionLight);
    
    JLabel Mother_Board = new JLabel("Mother Board ");
    Mother_Board.setToolTipText("\"Mother Board \" connection status");
    Mother_Board_Panel.add(Mother_Board);
    Mother_Board.setFont(new Font("新細明體", Font.PLAIN, 14));
    Mother_Board.setHorizontalAlignment(SwingConstants.LEFT);
    
    JLabel Xavier = new JLabel("NXT             ");
    Xavier.setToolTipText("\"Xavier\" connection status");
    Xavier.setHorizontalAlignment(SwingConstants.LEFT);
    Xavier.setFont(new Font("新細明體", Font.PLAIN, 14));
    NXT_Panel.add(Xavier);
    
    JLabel CTRL_Board = new JLabel("CTRL Board  ");
    CTRL_Board.setToolTipText("\"CTRL Board \" connection status");
    CTRL_Board.setHorizontalAlignment(SwingConstants.LEFT);
    CTRL_Board.setFont(new Font("新細明體", Font.PLAIN, 14));
    CTRL_Board_Panel.add(CTRL_Board);
    
    JLabel Brake_F = new JLabel("Brake  (F)      ");
    Brake_F.setToolTipText("\"Brake  (F)\" connection status");
    Brake_F.setHorizontalAlignment(SwingConstants.LEFT);
    Brake_F.setFont(new Font("新細明體", Font.PLAIN, 14));
    Brake_F_Panel.add(Brake_F);
    
    JLabel Brake_B = new JLabel("Brake  (B)      ");
    Brake_B.setToolTipText("\"Brake  (B)\" connection status");
    Brake_B.setHorizontalAlignment(SwingConstants.LEFT);
    Brake_B.setFont(new Font("新細明體", Font.PLAIN, 14));
    Brake_B_Panel.add(Brake_B);
    
    JLabel Distance_F = new JLabel("Distance (F)   ");
    Distance_F.setToolTipText("\"Distance (F)\" connection status");
    Distance_F.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_F.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_F_Panel.add(Distance_F);
    
    JLabel Distance_L = new JLabel("Distance (L)   ");
    Distance_L.setToolTipText("\"Distance (L)\" connection status");
    Distance_L.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_L.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_L_Panel.add(Distance_L);
    
    JLabel Distance_R = new JLabel("Distance (R)   ");
    Distance_R.setToolTipText("\"Distance (R)\" connection status");
    Distance_R.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_R.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_R_Panel.add(Distance_R);
    
    JLabel Distance_B = new JLabel("Distance (B)   ");
    Distance_B.setToolTipText("\"Distance (B)\" connection statua");
    Distance_B.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_B.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_B_Panel.add(Distance_B);
    
    JLabel Speed_Sensor = new JLabel("Speed Sensor  ");
    Speed_Sensor.setToolTipText("\"Speed Sensor\" connection status");
    Speed_Sensor.setHorizontalAlignment(SwingConstants.LEFT);
    Speed_Sensor.setFont(new Font("新細明體", Font.PLAIN, 14));
    Speed_Sensor_Panel.add(Speed_Sensor);
    
    JLabel Voltage_n_heat = new JLabel("Voltage & heat");
    Voltage_n_heat.setToolTipText("\"Voltage & heat\" connection status");
    Voltage_n_heat.setHorizontalAlignment(SwingConstants.LEFT);
    Voltage_n_heat.setFont(new Font("新細明體", Font.PLAIN, 14));
    Voltage_n_heat_Panel.add(Voltage_n_heat);
    
    JLabel Connection_Status = new JLabel("Connection Status");
    Connection_Status.setToolTipText("To see every microcontrollers' connection");
    Connection_Status.setForeground(new Color(107, 142, 35));
    Connection_Status.setHorizontalAlignment(SwingConstants.CENTER);
    Connection_Status.setFont(new Font("Arial", Font.BOLD, 20));
    scrollPane.setColumnHeaderView(Connection_Status);
    
    JLabel UID = new JLabel("UID :");
    UID.setHorizontalAlignment(SwingConstants.LEFT);
    UID.setFont(new Font("Arial Black", Font.PLAIN, 20));
    UID.setBounds(213, 12, 61, 24);
    frame.getContentPane().add(UID);
    
    JLabel Mother_Board_COM = new JLabel("Mother Board :");
    Mother_Board_COM.setHorizontalAlignment(SwingConstants.LEFT);
    Mother_Board_COM.setFont(new Font("Arial Black", Font.PLAIN, 20));
    Mother_Board_COM.setBounds(213, 63, 190, 24);
    frame.getContentPane().add(Mother_Board_COM);
    
    JLabel Front_Brake = new JLabel("Front Brake");
    Front_Brake.setHorizontalAlignment(SwingConstants.CENTER);
    Front_Brake.setFont(new Font("Arial", Font.PLAIN, 20));
    Front_Brake.setBounds(917, 10, 190, 24);
    frame.getContentPane().add(Front_Brake);
    
    JLabel Back_Brake = new JLabel("Back Brake");
    Back_Brake.setHorizontalAlignment(SwingConstants.CENTER);
    Back_Brake.setFont(new Font("Arial", Font.PLAIN, 20));
    Back_Brake.setBounds(1159, 10, 190, 24);
    frame.getContentPane().add(Back_Brake);
    
    JSeparator separator = new JSeparator();
    separator.setForeground(Color.LIGHT_GRAY);
    separator.setBounds(10, 603, 659, 2);
    frame.getContentPane().add(separator);
    
    JSeparator separator_1 = new JSeparator();
    separator_1.setForeground(Color.LIGHT_GRAY);
    separator_1.setBounds(11, 375, 658, 2);
    frame.getContentPane().add(separator_1);
    
    JSeparator separator_2 = new JSeparator();
    separator_2.setForeground(Color.LIGHT_GRAY);
    separator_2.setBounds(11, 250, 658, 2);
    frame.getContentPane().add(separator_2);
    
    JSeparator separator_3 = new JSeparator();
    separator_3.setForeground(Color.BLACK);
    separator_3.setBounds(11, 329, 658, 2);
    frame.getContentPane().add(separator_3);
    
    JSeparator separator_4 = new JSeparator();
    separator_4.setForeground(Color.BLACK);
    separator_4.setBounds(11, 557, 658, 2);
    frame.getContentPane().add(separator_4);
    
    JSeparator separator_5 = new JSeparator();
    separator_5.setForeground(Color.BLACK);
    separator_5.setBounds(11, 204, 658, 2);
    frame.getContentPane().add(separator_5);
    
    JSeparator separator_6 = new JSeparator();
    separator_6.setOrientation(SwingConstants.VERTICAL);
    separator_6.setForeground(Color.BLACK);
    separator_6.setBounds(669, 0, 8, 714);
    frame.getContentPane().add(separator_6);
    
    JSeparator separator_7 = new JSeparator();
    separator_7.setForeground(Color.BLACK);
    separator_7.setBounds(11, 451, 658, 2);
    frame.getContentPane().add(separator_7);
    
    JSeparator separator_8 = new JSeparator();
    separator_8.setForeground(Color.LIGHT_GRAY);
    separator_8.setBounds(11, 500, 658, 2);
    frame.getContentPane().add(separator_8);
    
    JSeparator separator_9 = new JSeparator();
    separator_9.setOrientation(SwingConstants.VERTICAL);
    separator_9.setForeground(Color.BLACK);
    separator_9.setBounds(10, 0, 8, 714);
    frame.getContentPane().add(separator_9);
    
    JSeparator separator_10 = new JSeparator();
    separator_10.setForeground(Color.BLACK);
    separator_10.setBounds(8, 0, 1369, 2);
    frame.getContentPane().add(separator_10);
    
    JSeparator separator_11 = new JSeparator();
    separator_11.setForeground(Color.LIGHT_GRAY);
    separator_11.setBounds(206, 46, 1171, 2);
    frame.getContentPane().add(separator_11);
    
    JSeparator separator_12 = new JSeparator();
    separator_12.setForeground(Color.BLACK);
    separator_12.setBounds(669, 102, 708, 2);
    frame.getContentPane().add(separator_12);
    
    JSeparator separator_13 = new JSeparator();
    separator_13.setOrientation(SwingConstants.VERTICAL);
    separator_13.setForeground(Color.BLACK);
    separator_13.setBounds(899, 0, 8, 103);
    frame.getContentPane().add(separator_13);
    
    JSeparator separator_14 = new JSeparator();
    separator_14.setOrientation(SwingConstants.VERTICAL);
    separator_14.setForeground(Color.BLACK);
    separator_14.setBounds(901, 0, 8, 103);
    frame.getContentPane().add(separator_14);
    
    JSeparator separator_15 = new JSeparator();
    separator_15.setOrientation(SwingConstants.VERTICAL);
    separator_15.setForeground(Color.BLACK);
    separator_15.setBounds(900, 0, 8, 103);
    frame.getContentPane().add(separator_15);
    
    JSeparator separator_16 = new JSeparator();
    separator_16.setForeground(Color.BLACK);
    separator_16.setBounds(669, 346, 708, 2);
    frame.getContentPane().add(separator_16);
    
    JSeparator separator_17 = new JSeparator();
    separator_17.setOrientation(SwingConstants.VERTICAL);
    separator_17.setForeground(Color.BLACK);
    separator_17.setBounds(1022, 102, 8, 246);
    frame.getContentPane().add(separator_17);
    
    JSeparator separator_18 = new JSeparator();
    separator_18.setForeground(Color.LIGHT_GRAY);
    separator_18.setBounds(204, 102, 468, 2);
    frame.getContentPane().add(separator_18);
    
    JSeparator separator_19 = new JSeparator();
    separator_19.setOrientation(SwingConstants.VERTICAL);
    separator_19.setForeground(Color.BLACK);
    separator_19.setBounds(1131, 0, 8, 103);
    frame.getContentPane().add(separator_19);
    
    JSeparator separator_20 = new JSeparator();
    separator_20.setOrientation(SwingConstants.VERTICAL);
    separator_20.setForeground(Color.BLACK);
    separator_20.setBounds(1060, 46, 8, 58);
    frame.getContentPane().add(separator_20);
    
    JSeparator separator_21 = new JSeparator();
    separator_21.setOrientation(SwingConstants.VERTICAL);
    separator_21.setForeground(Color.BLACK);
    separator_21.setBounds(1294, 46, 8, 58);
    frame.getContentPane().add(separator_21);
    
    JSeparator separator_22 = new JSeparator();
    separator_22.setForeground(Color.DARK_GRAY);
    separator_22.setBounds(669, 140, 708, 2);
    frame.getContentPane().add(separator_22);
    
    JLabel Motor_Temp = new JLabel("Motor Temperature");
    Motor_Temp.setFont(new Font("Arial", Font.PLAIN, 20));
    Motor_Temp.setBounds(116, 569, 171, 24);
    frame.getContentPane().add(Motor_Temp);
    
    JLabel Vehicle_Tilt_Angle = new JLabel("Vehicle Tilt Angle");
    Vehicle_Tilt_Angle.setFont(new Font("Arial", Font.PLAIN, 20));
    Vehicle_Tilt_Angle.setBounds(436, 569, 151, 24);
    frame.getContentPane().add(Vehicle_Tilt_Angle);
    
    JLabel Actual_motor_percentage = new JLabel("Actual Motor Percentage");
    Actual_motor_percentage.setHorizontalAlignment(SwingConstants.CENTER);
    Actual_motor_percentage.setFont(new Font("Arial", Font.PLAIN, 20));
    Actual_motor_percentage.setBounds(81, 341, 240, 24);
    frame.getContentPane().add(Actual_motor_percentage);
    
    JLabel Vichele_Speed = new JLabel("Vichele Speed");
    Vichele_Speed.setFont(new Font("Arial", Font.PLAIN, 20));
    Vichele_Speed.setBounds(448, 341, 127, 24);
    frame.getContentPane().add(Vichele_Speed);
    
    JLabel Controller_Perentage = new JLabel("Controller Percentage");
    Controller_Perentage.setHorizontalAlignment(SwingConstants.CENTER);
    Controller_Perentage.setFont(new Font("Arial", Font.PLAIN, 20));
    Controller_Perentage.setBounds(93, 216, 216, 24);
    frame.getContentPane().add(Controller_Perentage);
    
    JLabel Disable_or_enable_the_motor = new JLabel("Disable or enable the motor");
    Disable_or_enable_the_motor.setHorizontalAlignment(SwingConstants.CENTER);
    Disable_or_enable_the_motor.setFont(new Font("Arial", Font.PLAIN, 20));
    Disable_or_enable_the_motor.setBounds(390, 216, 250, 24);
    frame.getContentPane().add(Disable_or_enable_the_motor);
    
    JLabel Actual_Motor_Percentage_Control = new JLabel("Actual Motor Percentage Control");
    Actual_Motor_Percentage_Control.setFont(new Font("Arial", Font.PLAIN, 20));
    Actual_Motor_Percentage_Control.setBounds(204, 463, 288, 24);
    frame.getContentPane().add(Actual_Motor_Percentage_Control);

    JLabel Battery_Percentage = new JLabel("Battery percentage");
    Battery_Percentage.setHorizontalAlignment(SwingConstants.CENTER);
    Battery_Percentage.setFont(new Font("Arial", Font.PLAIN, 20));
    Battery_Percentage.setBounds(689, 12, 190, 24);
    frame.getContentPane().add(Battery_Percentage);
    
    JLabel Mother_Board_Serial = new JLabel("Mother Board Serial");
    Mother_Board_Serial.setForeground(new Color(51, 204, 204));
    Mother_Board_Serial.setHorizontalAlignment(SwingConstants.CENTER);
    Mother_Board_Serial.setFont(new Font("Arial", Font.PLAIN, 20));
    Mother_Board_Serial.setBounds(750, 110, 190, 24);
    frame.getContentPane().add(Mother_Board_Serial);
    
    JLabel NXT_Serial = new JLabel("Xavier Serial");
    NXT_Serial.setForeground(new Color(51, 204, 204));
    NXT_Serial.setHorizontalAlignment(SwingConstants.CENTER);
    NXT_Serial.setFont(new Font("Arial", Font.PLAIN, 20));
    NXT_Serial.setBounds(1118, 110, 190, 24);
    frame.getContentPane().add(NXT_Serial);
    
    JLabel Rader = new JLabel("Rader");
    Rader.setHorizontalAlignment(SwingConstants.LEFT);
    Rader.setFont(new Font("Arial", Font.PLAIN, 20));
    Rader.setBounds(681, 350, 61, 24);
    frame.getContentPane().add(Rader);
    
    JLabel Wheelchair_figure = new JLabel("");
    Wheelchair_figure.setToolTipText("Wheelchair");
    Wheelchair_figure.setIcon(new ImageIcon("D:\\AutoBrake_ComputerSite_System\\image\\wheelChair_TOP.png"));
    Wheelchair_figure.setBounds(899, 451, 151, 151);
    frame.getContentPane().add(Wheelchair_figure);
    
    Motor_Temp_V = new JLabel("25\u00B0C");
    Motor_Temp_V.setToolTipText("The temperature renew per half second");
    Motor_Temp_V.setHorizontalAlignment(SwingConstants.CENTER);
    Motor_Temp_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Motor_Temp_V.setBounds(137, 603, 129, 58);
    frame.getContentPane().add(Motor_Temp_V);

    Vichele_Tilt_Angle_V = new JLabel("0\u00B0");
    Vichele_Tilt_Angle_V.setToolTipText("Angle renew per 10 millisecond");
    Vichele_Tilt_Angle_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Tilt_Angle_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Tilt_Angle_V.setBounds(457, 603, 108, 58);
    frame.getContentPane().add(Vichele_Tilt_Angle_V);

    Vichele_Speed_V = new JLabel("0 km/hr");
    Vichele_Speed_V.setToolTipText("Speed Value renew immediately");
    Vichele_Speed_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Speed_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Speed_V.setBounds(405, 375, 219, 58);
    frame.getContentPane().add(Vichele_Speed_V);

    Actual_motor_percentage_V = new JLabel("0%");
    Actual_motor_percentage_V.setToolTipText("Motor percentage value renew immediately");
    Actual_motor_percentage_V.setHorizontalAlignment(SwingConstants.CENTER);
    Actual_motor_percentage_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Actual_motor_percentage_V.setBounds(144, 375, 115, 58);
    frame.getContentPane().add(Actual_motor_percentage_V);

    Controller_Perentage_V = new JLabel("0%");
    Controller_Perentage_V.setToolTipText("Controller percentage renew immediately");
    Controller_Perentage_V.setHorizontalAlignment(SwingConstants.CENTER);
    Controller_Perentage_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Controller_Perentage_V.setBounds(133, 250, 137, 58);
    frame.getContentPane().add(Controller_Perentage_V);

    Battery_Percentage_V = new JLabel("0%");
    Battery_Percentage_V.setToolTipText("Battery percentage renew per minute when vehicle motor has no apply");
    Battery_Percentage_V.setHorizontalAlignment(SwingConstants.CENTER);
    Battery_Percentage_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Battery_Percentage_V.setBounds(716, 46, 137, 58);
    frame.getContentPane().add(Battery_Percentage_V);

    Front_Brake_V = new JLabel("0 N");
    Front_Brake_V.setToolTipText("Front Brake Valuerenew immediately");
    Front_Brake_V.setHorizontalAlignment(SwingConstants.CENTER);
    Front_Brake_V.setForeground(new Color(0, 0, 0));
    Front_Brake_V.setFont(new Font("Arial", Font.PLAIN, 20));
    Front_Brake_V.setBounds(1062, 63, 69, 24);
    frame.getContentPane().add(Front_Brake_V);

    Back_Brake_V = new JLabel("0 N");
    Back_Brake_V.setToolTipText("Back Brake Valuerenew immediately");
    Back_Brake_V.setHorizontalAlignment(SwingConstants.CENTER);
    Back_Brake_V.setForeground(Color.BLACK);
    Back_Brake_V.setFont(new Font("Arial", Font.PLAIN, 20));
    Back_Brake_V.setBounds(1296, 63, 69, 24);
    frame.getContentPane().add(Back_Brake_V);
    
    JLabel UID_No = new JLabel("0000000000");
    UID_No.setToolTipText("The UID number of the user");
    UID_No.setForeground(Color.DARK_GRAY);
    UID_No.setHorizontalAlignment(SwingConstants.LEFT);
    UID_No.setFont(new Font("Consolas", Font.PLAIN, 28));
    UID_No.setBounds(284, 12, 190, 36);
    frame.getContentPane().add(UID_No);
    
    Mother_Board_Serial_List = new List();
    Mother_Board_Serial_List.setMultipleSelections(false);
    Mother_Board_Serial_List.setFont(new Font("Arial", Font.PLAIN, 18));
    Mother_Board_Serial_List.setBounds(673, 140, 348, 165);
    frame.getContentPane().add(Mother_Board_Serial_List);
    
    NXT_Serial_List = new List();
    NXT_Serial_List.setMultipleSelections(false);
    NXT_Serial_List.setFont(new Font("Arial", Font.PLAIN, 18));
    NXT_Serial_List.setBounds(1026, 140, 348, 165);
    frame.getContentPane().add(NXT_Serial_List);
    
    
    
// Interactive components

  //Motor
    Disable_or_enable_the_motor_Button = new JButton("ENABLE");
    Disable_or_enable_the_motor_Button.setActionCommand("Tap to ENABLE");
    Disable_or_enable_the_motor_Button.setBackground(Color.GREEN);
    Disable_or_enable_the_motor_Button.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Disable_or_enable_the_motor_Button.setBounds(405, 262, 219, 43);
    frame.getContentPane().add(Disable_or_enable_the_motor_Button);
    
    Actual_Motor_Percentage_Control_Slider = new JSlider();
    Actual_Motor_Percentage_Control_Slider.setToolTipText("Slide the bar as the controller,REMEMBER to ENABLE the motor");
    Actual_Motor_Percentage_Control_Slider.setPaintLabels(true);
    Actual_Motor_Percentage_Control_Slider.setSnapToTicks(true);
    Actual_Motor_Percentage_Control_Slider.setBackground(Color.WHITE);
    Actual_Motor_Percentage_Control_Slider.setForeground(Color.GREEN);
    Actual_Motor_Percentage_Control_Slider.setValue(0);
    Actual_Motor_Percentage_Control_Slider.setBounds(21, 505, 644, 48);
    frame.getContentPane().add(Actual_Motor_Percentage_Control_Slider);
    
  //Connection
    COM_selection_comboBox = new JComboBox<String>();
    COM_selection_comboBox.setBackground(Color.WHITE);
    COM_selection_comboBox.setFont(new Font("Arial Rounded MT Bold", Font.PLAIN, 23));
    COM_selection_comboBox.setToolTipText("Choose Mother Board COM number");
    COM_selection_comboBox.setBounds(379, 58, 151, 34);
    SerialPort[] portNames = SerialPort.getCommPorts();
    for(int i = 0; i < portNames.length; i++) COM_selection_comboBox.addItem(portNames[i].getSystemPortName());
    frame.getContentPane().add(COM_selection_comboBox);
    
    JButton Dis_Connect = new JButton("Connect");
    Dis_Connect.setForeground(Color.BLACK);
    Dis_Connect.setBackground(Color.WHITE);
    Dis_Connect.setBounds(536, 58, 123, 34);
    frame.getContentPane().add(Dis_Connect);
    
  //Mother Board Serial
    JFormattedTextField Mother_Board_Serial_TextBox = new JFormattedTextField();
    Mother_Board_Serial_TextBox.setToolTipText("<English only>  \r\nType here to send message to Mother Board via Serial");
    Mother_Board_Serial_TextBox.setFont(new Font("Constantia", Font.PLAIN, 14));
    Mother_Board_Serial_TextBox.setBounds(671, 307, 277, 38);
    frame.getContentPane().add(Mother_Board_Serial_TextBox);
    
    Button Mother_Board_Serial_SendButton = new Button("Send");
    Mother_Board_Serial_SendButton.setBounds(946, 307, 76, 38);
    frame.getContentPane().add(Mother_Board_Serial_SendButton);
    
  //NXT Serial
    JFormattedTextField NXT_Serial_TextBox = new JFormattedTextField();
    NXT_Serial_TextBox.setToolTipText("<English only>  \r\nType here to send message to NXT via Serial");
    NXT_Serial_TextBox.setFont(new Font("Constantia", Font.PLAIN, 14));
    NXT_Serial_TextBox.setBounds(1024, 307, 277, 38);
    frame.getContentPane().add(NXT_Serial_TextBox);
    
    Button NXT_Serial_SendButton = new Button("Send");
    NXT_Serial_SendButton.setBounds(1298, 307, 76, 38);
    frame.getContentPane().add(NXT_Serial_SendButton);

  //Front Brake
    Front_Brake_Slider = new JSlider();
    Front_Brake_Slider.setToolTipText("Slide to controller FRONT brake");
    Front_Brake_Slider.setBackground(Color.WHITE);
    Front_Brake_Slider.setForeground(Color.WHITE);
    Front_Brake_Slider.setSnapToTicks(true);
    Front_Brake_Slider.setPaintLabels(true);
    Front_Brake_Slider.setValue(0);
    Front_Brake_Slider.setBounds(903, 62, 156, 26);
    frame.getContentPane().add(Front_Brake_Slider);
    
  //Back Brake
    Back_Brake_Slider = new JSlider();
    Back_Brake_Slider.setToolTipText("Slide to controller BACK brake");
    Back_Brake_Slider.setBackground(Color.WHITE);
    Back_Brake_Slider.setForeground(Color.WHITE);
    Back_Brake_Slider.setValue(0);
    Back_Brake_Slider.setSnapToTicks(true);
    Back_Brake_Slider.setPaintLabels(true);
    Back_Brake_Slider.setBounds(1134, 62, 159, 26);
    frame.getContentPane().add(Back_Brake_Slider);
    
  //Logout
    Button Logout_Button = new Button("Log Out");
    Logout_Button.setBounds(583, 13, 76, 23);
    frame.getContentPane().add(Logout_Button);
    
    
    
    
//Listener
  //Connection
    Disable_or_enable_the_motor_Button.addActionListener(new ActionListener(){
      @Override 
      public void actionPerformed(ActionEvent arg0) {
        if(Disable_or_enable_the_motor_Button.getText().equals("ENABLE")) {
            Disable_or_enable_the_motor_Button.setBackground(Color.RED);
            Disable_or_enable_the_motor_Button.setText("DISABLE");
            Disable_or_enable_the_motor_Button.setActionCommand("Tap to DISABLE");
            SimpleDateFormat time = new SimpleDateFormat("yyyy,MM,dd,HH,mm,ss,SSS");
            String timeS = time.toString();
            String send = "@"+ timeS + " ";
            print(send);
        }
        else if (Disable_or_enable_the_motor_Button.getText().equals("DISABLE")) {
            Disable_or_enable_the_motor_Button.setBackground(Color.GREEN);
            Disable_or_enable_the_motor_Button.setText("ENABLE");
            Disable_or_enable_the_motor_Button.setActionCommand("Tap to ENABLE");
            print("# ");
        }
      }
    });
    
  //Motor
    Actual_Motor_Percentage_Control_Slider.addChangeListener(new ChangeListener() {
      public void stateChanged(ChangeEvent e) {
        JSlider source = (JSlider)e.getSource();
        if (!source.getValueIsAdjusting()) {
          int slideValue = (int)source.getValue();
          String Controller_Perentage_Value = slideValue +"%";
          Controller_Perentage_V.setText(Controller_Perentage_Value);
          print("M"+slideValue+" ");
        }
      }
    });
    
    Dis_Connect.addActionListener(new ActionListener(){
      @Override 
      public void actionPerformed(ActionEvent arg0) {
        if(Dis_Connect.getText().equals("Connect")) {
          // attempt to connect to the serial port
          chosenPort = SerialPort.getCommPort(COM_selection_comboBox.getSelectedItem().toString());
          chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER, 0, 0);
          if(chosenPort.openPort()) {
            Dis_Connect.setText("Disconnect");
            COM_selection_comboBox.setEnabled(false);
            hasChoosePort = true ;
            SimpleDateFormat time = new SimpleDateFormat("yyyy,MM,dd,HH,mm,ss,SSS");
            String timeS = time.toString();
            String send = "@"+ timeS ;
            print(send);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            print("$C ");
          }
        }
        else {
          // disconnect from the serial port
          print("$D ");
          chosenPort.closePort();
          hasChoosePort = false;
          COM_selection_comboBox.setEnabled(true);
          Dis_Connect.setText("Connect");
        }
      }
    });
    
    Front_Brake_Slider.addChangeListener(new ChangeListener() {
      public void stateChanged(ChangeEvent e) {
        JSlider source = (JSlider)e.getSource();
        if (!source.getValueIsAdjusting()) {
          int slideValue = (int)source.getValue();
          String Front_Brake_Value = slideValue +" N";
          Front_Brake_V.setText(Front_Brake_Value);
          print("F"+slideValue+" ");
        }
      }
    });
    
    Back_Brake_Slider.addChangeListener(new ChangeListener() {
        public void stateChanged(ChangeEvent e) {
          JSlider source = (JSlider)e.getSource();
          if (!source.getValueIsAdjusting()) {
            int slideValue = (int)source.getValue();
            String Back_Brake_Value = slideValue +" N";
            Back_Brake_V.setText(Back_Brake_Value);
            print("D"+slideValue+" ");
          }
        }
      });
    
  //Mother board Serial
    Mother_Board_Serial_TextBox.addKeyListener(new KeyAdapter() {
      @Override
      public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (Mother_Board_Serial_TextBox.getText()!=null && key == KeyEvent.VK_ENTER) {
          Mother_Board_Serial_List.add(Mother_Board_Serial_TextBox.getText());
          print("H"+Mother_Board_Serial_TextBox.getText());
//                JScrollPane messageScrollList = new JScrollPane(list);
//            messageScrollList.getVerticalScrollBar().addAdjustmentListener(new AdjustmentListener() {
//                public void adjustmentValueChanged(AdjustmentEvent e) {  
//                    e.getAdjustable().setValue(e.getAdjustable().getMaximum());  
//                } 
//            });
//            JScrollBar scrolllistBar = scrolllist.getVerticalScrollBar();
//            scrolllistBar.setValue(scrolllistBar.getMaximum());
        Mother_Board_Serial_TextBox.setText(null);
      }
      if (key == KeyEvent.VK_DELETE ) {
          Mother_Board_Serial_List.clear();
      }
      }
    });
    
    Mother_Board_Serial_SendButton.addMouseListener(new MouseAdapter() {
      @Override
      public void mousePressed(MouseEvent e) {
        Mother_Board_Serial_List.add(Mother_Board_Serial_TextBox.getText());
        print("H"+Mother_Board_Serial_TextBox.getText());
        Mother_Board_Serial_TextBox.setText(null);
      }
    });
    
  //NXT Serial
    NXT_Serial_TextBox.addKeyListener(new KeyAdapter() {
      @Override
      public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (NXT_Serial_TextBox.getText()!=null && key == KeyEvent.VK_ENTER) {
          NXT_Serial_List.add(NXT_Serial_TextBox.getText());
          print("N"+NXT_Serial_TextBox.getText());
          NXT_Serial_TextBox.setText(null);
        }
        if (key == KeyEvent.VK_DELETE ) {
          NXT_Serial_List.clear();
        }
      }
    });
    
    NXT_Serial_SendButton.addMouseListener(new MouseAdapter() {
      @Override
      public void mousePressed(MouseEvent e) {
        NXT_Serial_List.add(NXT_Serial_TextBox.getText());
        print("N"+NXT_Serial_TextBox.getText());
        NXT_Serial_TextBox.setText(null);
      }
    });
    
    frame.setVisible(true);
  }
  
static class RemindTask extends TimerTask {
  public void run() {
   read();
  }
}
 static void read() {
  while (hasChoosePort) {
    @SuppressWarnings("resource")
    Scanner scannerS /*System*/ = new Scanner(System.in);
    if (scannerS.hasNext()) {
        String line = scannerS.nextLine();
        print(line);
    }
    Scanner scannerSC/*Serial COMM*/ = new Scanner(chosenPort.getInputStream());
    if (scannerSC.hasNext()) {
      try {
        String line = scannerSC.nextLine();
        System.out.println(line);
        char in = line.charAt(0);
        switch(in) {
          case '@':{
            Disable_or_enable_the_motor_Button.setBackground(Color.RED);
            Disable_or_enable_the_motor_Button.setText("DISABLE");
            Disable_or_enable_the_motor_Button.setActionCommand("Tap to DISABLE");
            break;
          }
          case '#':{
            Disable_or_enable_the_motor_Button.setBackground(Color.GREEN);
            Disable_or_enable_the_motor_Button.setText("ENABLE");
            Disable_or_enable_the_motor_Button.setActionCommand("Tap to ENABLE");
            break;
          }
          case '?':{
            char CSin = line.charAt(1);
            switch (CSin) {
              case 'A':{
                if (Mother_Board_ConditionLight.getForeground()==Color.RED) {
                  Mother_Board_ConditionLight.setForeground(Color.GREEN);
                  Mother_Board_ConditionLight.setToolTipText("connected");
                }
                else {
                  Mother_Board_ConditionLight.setForeground(Color.RED);
                  Mother_Board_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'N':{
                if (NXT_ConditionLight.getForeground()==Color.RED) {
                  NXT_ConditionLight.setForeground(Color.GREEN);
                  NXT_ConditionLight.setToolTipText("connected");
                }
                else {
                  NXT_ConditionLight.setForeground(Color.RED);
                  NXT_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'X':{
                if (CTRL_Board_ConditionLight.getForeground()==Color.RED) {
                  CTRL_Board_ConditionLight.setForeground(Color.GREEN);
                  CTRL_Board_ConditionLight.setToolTipText("connected");
                }
                else {
                  CTRL_Board_ConditionLight.setForeground(Color.RED);
                  CTRL_Board_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'E':{
                if (Brake_F_ConditionLight.getForeground()==Color.RED) {
                  Brake_F_ConditionLight.setForeground(Color.GREEN);
                  Brake_F_ConditionLight.setToolTipText("connected");
                }
                else {
                  Brake_F_ConditionLight.setForeground(Color.RED);
                  Brake_F_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'D':{
                if (Brake_B_ConditionLight.getForeground()==Color.RED) {
                  Brake_B_ConditionLight.setForeground(Color.GREEN);
                  Brake_B_ConditionLight.setToolTipText("connected");
                }
                else {
                  Brake_B_ConditionLight.setForeground(Color.RED);
                  Brake_B_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'F':{
                if (Distance_F_ConditionLight.getForeground()==Color.RED) {
                  Distance_F_ConditionLight.setForeground(Color.GREEN);
                  Distance_F_ConditionLight.setToolTipText("connected");
                }
                else {
                  Distance_F_ConditionLight.setForeground(Color.RED);
                  Distance_F_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'L':{
                if (Distance_L_ConditionLight.getForeground()==Color.RED) {
                  Distance_L_ConditionLight.setForeground(Color.GREEN);
                  Distance_L_ConditionLight.setToolTipText("connected");
                }
                else {
                    Distance_L_ConditionLight.setForeground(Color.RED);
                    Distance_L_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'R':{
                if (Distance_R_ConditionLight.getForeground()==Color.RED) {
                  Distance_R_ConditionLight.setForeground(Color.GREEN);
                  Distance_R_ConditionLight.setToolTipText("connected");
                }
                else {
                    Distance_R_ConditionLight.setForeground(Color.RED);
                    Distance_R_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'C':{
                if (Distance_B_ConditionLight.getForeground()==Color.RED) {
                  Distance_B_ConditionLight.setForeground(Color.GREEN);
                  Distance_B_ConditionLight.setToolTipText("connected");
                }
                else {
                    Distance_B_ConditionLight.setForeground(Color.RED);
                    Distance_B_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'S':{
                if (Speed_Sensor_ConditionLight.getForeground()==Color.RED) {
                  Speed_Sensor_ConditionLight.setForeground(Color.GREEN);
                  Speed_Sensor_ConditionLight.setToolTipText("connected");
                }
                else {
                    Speed_Sensor_ConditionLight.setForeground(Color.RED);
                    Speed_Sensor_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
              case 'T':{
                if (Voltage_n_heat_ConditionLight.getForeground()==Color.RED) {
                  Voltage_n_heat_ConditionLight.setForeground(Color.GREEN);
                  Voltage_n_heat_ConditionLight.setToolTipText("connected");
                }
                else {
                    Voltage_n_heat_ConditionLight.setForeground(Color.RED);
                    Voltage_n_heat_ConditionLight.setToolTipText("disconnect");
                }
                break;
              }
            }
          }
          case 'X':{
            line = line.replaceAll("X", "");
            int num = Integer.parseInt(line);
            Controller_Perentage_V.setText(num+"%");
            Actual_Motor_Percentage_Control_Slider.setValue(num);
            break;
          }
          case 'M':{
            line = line.replaceAll("M", "");
            int num = Integer.parseInt(line);
            Actual_motor_percentage_V.setText(num+"%");
            break;
          }
          case 'V':{
            line = line.replaceAll("V", "");
            int num = Integer.parseInt(line);
            double speed = num / 100.00;
            Vichele_Speed_V.setText(speed+" km/hr");
            break;
          }
          case 'T':{
            line = line.replaceAll("T", "");
            int num = Integer.parseInt(line);
            System.out.println(num);
            Motor_Temp_V.setText(line+"\u00B0C");
            break;
          }
          case 'A':{
            line = line.replaceAll("A", "");
            int num = Integer.parseInt(line);
            Vichele_Tilt_Angle_V.setText(num+"\u00B0");
            break;
          }
          case 'B':{
            line = line.replaceAll("B", "");
            int num = Integer.parseInt(line);
            Battery_Percentage_V.setText(num+" %");
            break;
          }
          case 'E':{
            line = line.replaceAll("E", "");
            int num = Integer.parseInt(line);
            Front_Brake_V.setText(num+" N");
            Front_Brake_Slider.setValue(num);
            break;
          }
          case 'D':{
            line = line.replaceAll("D", "");
            int num = Integer.parseInt(line);
            Back_Brake_V.setText(num+" N");
            Back_Brake_Slider.setValue(num);
            break;
          }
          case 'H':{
            String MotherSerial = "";
            for (int i=1; i<line.length(); i++) {
              char a = line.charAt(i);
              MotherSerial = MotherSerial + a ;
            }
            Mother_Board_Serial_List.add(MotherSerial);
            break;
          }
          case 'N':{
            String NXTSerial = "";
            for (int i=1; i<line.length(); i++) {
              char a = line.charAt(i);
              NXTSerial = NXTSerial + a ;
            }
            NXT_Serial_List.add(NXTSerial);
            break;
          }
          //Front distance Sensor
          case 'F':{
              break;
          }
          //Left distance Sensor
          case 'L':{
              break;
          }
          //Back distance Sensor
          case 'C':{
              break;
          }
          //Right distance Sensor
          case 'R':{
              break;
          }
        }
          frame.repaint();
      }
      catch(Exception e) {}
    }
    scannerSC.close();
  }
}
  static void print(String send) {
    if (hasChoosePort) {
      PrintWriter output = new PrintWriter (chosenPort.getOutputStream());
      output.print(send);
      System.out.println(send);
      output.flush();
    }
  }
}