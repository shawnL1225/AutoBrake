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
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;
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

  static JFrame frmMsbaautobrakecomputersitesystem;
  
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
  static JLabel Heat_n_Gsensor__ConditionLight;
  
  static JLabel Motor_Temp_V;
  static JLabel Vichele_Tilt_Angle_V;
  static JLabel Vichele_Speed_V;
  static JLabel Controller_Perentage_V;
  static JLabel Battery_Percentage_V;
  static JLabel Front_Brake_V;
  static JLabel Back_Brake_V;
  static JLabel Vichele_Rise_Angle_V;
  static JLabel Vichele_Acc_V; 
  
  static JLabel distance_sensor_R_1;
  static JLabel distance_sensor_R_2;
  static JLabel distance_sensor_R_3;
  static JLabel distance_sensor_R_4;
  static JLabel distance_sensor_R_5;
  static JLabel distance_sensor_L_1;
  static JLabel distance_sensor_L_2;
  static JLabel distance_sensor_L_3;
  static JLabel distance_sensor_L_4;
  static JLabel distance_sensor_L_5;
  static JLabel distance_sensor_B_R;
  static JLabel distance_sensor_B_L;
  static JLabel distance_sensor_B_M;
  static JLabel distance_sensor_R_1_V;
  static JLabel distance_sensor_R_2_V;
  static JLabel distance_sensor_R_3_V;
  static JLabel distance_sensor_R_4_V;
  static JLabel distance_sensor_R_5_V;
  static JLabel distance_sensor_L_1_V;
  static JLabel distance_sensor_L_2_V;
  static JLabel distance_sensor_L_3_V;
  static JLabel distance_sensor_L_4_V;
  static JLabel distance_sensor_L_5_V;
  static JLabel distance_sensor_B_R_V;
  static JLabel distance_sensor_B_L_V;
  static JLabel distance_sensor_B_M_V;
  
  
  static JSlider Actual_Motor_Percentage_Control_Slider;
  static JSlider Front_Brake_Slider;
  static JSlider Back_Brake_Slider;
  static JSlider Rader_ON_OFF_Slide;
  
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
    timer.scheduleAtFixedRate(new RemindTask(),0, 2);
    frmMsbaautobrakecomputersitesystem = new JFrame();
    frmMsbaautobrakecomputersitesystem.setTitle("MSBA_AutoBrake_ComputerSite_System");
    frmMsbaautobrakecomputersitesystem.setIconImage(Toolkit.getDefaultToolkit().getImage("D:\\AutoBrake\\Auto_Brake_ComputerSite_System_Code\\image\\MSBA_icon.png"));
    frmMsbaautobrakecomputersitesystem.getContentPane().setBackground(Color.WHITE);
    frmMsbaautobrakecomputersitesystem.setBounds(100, 100, 450, 300);
    frmMsbaautobrakecomputersitesystem.setExtendedState(JFrame.MAXIMIZED_BOTH); 
    frmMsbaautobrakecomputersitesystem.setSize(1650,1080);
    frmMsbaautobrakecomputersitesystem.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frmMsbaautobrakecomputersitesystem.getContentPane().setLayout(null);
    
    JScrollPane scrollPane = new JScrollPane(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    scrollPane.setBounds(10, 0, 195, 206);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(scrollPane);
    
    Box verticalBox_1 = Box.createVerticalBox();
    scrollPane.setViewportView(verticalBox_1);
    
    Panel Mother_Board_Panel = new Panel();
    verticalBox_1.add(Mother_Board_Panel);
    
    Panel Caculation_chip_Panel = new Panel();
    verticalBox_1.add(Caculation_chip_Panel);
    
    JLabel Caculation_chip_ConditionLight_1 = new JLabel("\u25CF");
    Caculation_chip_ConditionLight_1.setToolTipText("disconnect");
    Caculation_chip_ConditionLight_1.setForeground(Color.RED);
    Caculation_chip_ConditionLight_1.setFont(new Font("新細明體", Font.PLAIN, 16));
    Caculation_chip_ConditionLight_1.setAlignmentY(0.0f);
    Caculation_chip_Panel.add(Caculation_chip_ConditionLight_1);
    
    JLabel Caculation_chip = new JLabel("Caculation chip");
    Caculation_chip.setToolTipText("Caculation chip \" connection status");
    Caculation_chip.setHorizontalAlignment(SwingConstants.LEFT);
    Caculation_chip.setFont(new Font("新細明體", Font.PLAIN, 14));
    Caculation_chip_Panel.add(Caculation_chip);
    
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
    
    Panel Heat_n_Gsensor_Panel = new Panel();
    verticalBox_1.add(Heat_n_Gsensor_Panel);
    
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

    Heat_n_Gsensor__ConditionLight = new JLabel("\u25CF");
    Heat_n_Gsensor__ConditionLight.setToolTipText("disconnect");
    Heat_n_Gsensor__ConditionLight.setForeground(Color.RED);
    Heat_n_Gsensor__ConditionLight.setFont(new Font("新細明體", Font.PLAIN, 16));
    Heat_n_Gsensor_Panel.add(Heat_n_Gsensor__ConditionLight);
    
    JLabel Mother_Board = new JLabel("Mother Board   ");
    Mother_Board.setToolTipText("\"Mother Board \" connection status");
    Mother_Board_Panel.add(Mother_Board);
    Mother_Board.setFont(new Font("新細明體", Font.PLAIN, 14));
    Mother_Board.setHorizontalAlignment(SwingConstants.LEFT);
    
    JLabel Xavier = new JLabel("XAVIER          ");
    Xavier.setToolTipText("\"Xavier\" connection status");
    Xavier.setHorizontalAlignment(SwingConstants.LEFT);
    Xavier.setFont(new Font("新細明體", Font.PLAIN, 14));
    NXT_Panel.add(Xavier);
    
    JLabel CTRL_Board = new JLabel("CTRL Board     ");
    CTRL_Board.setToolTipText("\"CTRL Board \" connection status");
    CTRL_Board.setHorizontalAlignment(SwingConstants.LEFT);
    CTRL_Board.setFont(new Font("新細明體", Font.PLAIN, 14));
    CTRL_Board_Panel.add(CTRL_Board);
    
    JLabel Brake_F = new JLabel("Brake  (F)         ");
    Brake_F.setToolTipText("\"Brake  (F)\" connection status");
    Brake_F.setHorizontalAlignment(SwingConstants.LEFT);
    Brake_F.setFont(new Font("新細明體", Font.PLAIN, 14));
    Brake_F_Panel.add(Brake_F);
    
    JLabel Brake_B = new JLabel("Brake  (B)        ");
    Brake_B.setToolTipText("\"Brake  (B)\" connection status");
    Brake_B.setHorizontalAlignment(SwingConstants.LEFT);
    Brake_B.setFont(new Font("新細明體", Font.PLAIN, 14));
    Brake_B_Panel.add(Brake_B);
    
    JLabel Distance_F = new JLabel("Distance (F)     ");
    Distance_F.setToolTipText("\"Distance (F)\" connection status");
    Distance_F.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_F.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_F_Panel.add(Distance_F);
    
    JLabel Distance_L = new JLabel("Distance (L)     ");
    Distance_L.setToolTipText("\"Distance (L)\" connection status");
    Distance_L.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_L.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_L_Panel.add(Distance_L);
    
    JLabel Distance_R = new JLabel("Distance (R)     ");
    Distance_R.setToolTipText("\"Distance (R)\" connection status");
    Distance_R.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_R.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_R_Panel.add(Distance_R);
    
    JLabel Distance_B = new JLabel("Distance (B)     ");
    Distance_B.setToolTipText("\"Distance (B)\" connection statua");
    Distance_B.setHorizontalAlignment(SwingConstants.LEFT);
    Distance_B.setFont(new Font("新細明體", Font.PLAIN, 14));
    Distance_B_Panel.add(Distance_B);
    
    JLabel Speed_Sensor = new JLabel("Speed Sensor    ");
    Speed_Sensor.setToolTipText("\"Speed Sensor\" connection status");
    Speed_Sensor.setHorizontalAlignment(SwingConstants.LEFT);
    Speed_Sensor.setFont(new Font("新細明體", Font.PLAIN, 14));
    Speed_Sensor_Panel.add(Speed_Sensor);
    
    JLabel Heat_n_Gsensor = new JLabel("Heat & Gsensor");
    Heat_n_Gsensor.setToolTipText("\"Heat & Gsensor\" connection status");
    Heat_n_Gsensor.setHorizontalAlignment(SwingConstants.LEFT);
    Heat_n_Gsensor.setFont(new Font("新細明體", Font.PLAIN, 14));
    Heat_n_Gsensor_Panel.add(Heat_n_Gsensor);
    
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
    frmMsbaautobrakecomputersitesystem.getContentPane().add(UID);
    
    JLabel Mother_Board_COM = new JLabel("Mother Board :");
    Mother_Board_COM.setHorizontalAlignment(SwingConstants.LEFT);
    Mother_Board_COM.setFont(new Font("Arial Black", Font.PLAIN, 20));
    Mother_Board_COM.setBounds(213, 63, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Mother_Board_COM);
    
    JLabel Front_Brake = new JLabel("Front Brake");
    Front_Brake.setHorizontalAlignment(SwingConstants.CENTER);
    Front_Brake.setFont(new Font("Arial", Font.PLAIN, 20));
    Front_Brake.setBounds(917, 10, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Front_Brake);
    
    JLabel Back_Brake = new JLabel("Back Brake");
    Back_Brake.setHorizontalAlignment(SwingConstants.CENTER);
    Back_Brake.setFont(new Font("Arial", Font.PLAIN, 20));
    Back_Brake.setBounds(1159, 10, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Back_Brake);
    
    JSeparator separator = new JSeparator();
    separator.setForeground(Color.LIGHT_GRAY);
    separator.setBounds(10, 603, 659, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator);
    
    JSeparator separator_1 = new JSeparator();
    separator_1.setForeground(Color.LIGHT_GRAY);
    separator_1.setBounds(11, 375, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_1);
    
    JSeparator separator_2 = new JSeparator();
    separator_2.setForeground(Color.LIGHT_GRAY);
    separator_2.setBounds(11, 250, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_2);
    
    JSeparator separator_3 = new JSeparator();
    separator_3.setForeground(Color.BLACK);
    separator_3.setBounds(11, 329, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_3);
    
    JSeparator separator_4 = new JSeparator();
    separator_4.setForeground(Color.BLACK);
    separator_4.setBounds(11, 557, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_4);
    
    JSeparator separator_5 = new JSeparator();
    separator_5.setForeground(Color.BLACK);
    separator_5.setBounds(11, 204, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_5);
    
    JSeparator separator_6 = new JSeparator();
    separator_6.setOrientation(SwingConstants.VERTICAL);
    separator_6.setForeground(Color.BLACK);
    separator_6.setBounds(669, 0, 8, 714);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_6);
    
    JSeparator separator_7 = new JSeparator();
    separator_7.setForeground(Color.BLACK);
    separator_7.setBounds(11, 451, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_7);
    
    JSeparator separator_8 = new JSeparator();
    separator_8.setForeground(Color.LIGHT_GRAY);
    separator_8.setBounds(11, 500, 658, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_8);
    
    JSeparator separator_9 = new JSeparator();
    separator_9.setOrientation(SwingConstants.VERTICAL);
    separator_9.setForeground(Color.BLACK);
    separator_9.setBounds(10, 0, 8, 714);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_9);
    
    JSeparator separator_10 = new JSeparator();
    separator_10.setForeground(Color.BLACK);
    separator_10.setBounds(8, 0, 1369, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_10);
    
    JSeparator separator_11 = new JSeparator();
    separator_11.setForeground(Color.LIGHT_GRAY);
    separator_11.setBounds(206, 46, 1171, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_11);
    
    JSeparator separator_12 = new JSeparator();
    separator_12.setForeground(Color.BLACK);
    separator_12.setBounds(669, 102, 708, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_12);
    
    JSeparator separator_13 = new JSeparator();
    separator_13.setOrientation(SwingConstants.VERTICAL);
    separator_13.setForeground(Color.BLACK);
    separator_13.setBounds(899, 0, 8, 103);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_13);
    
    JSeparator separator_14 = new JSeparator();
    separator_14.setOrientation(SwingConstants.VERTICAL);
    separator_14.setForeground(Color.BLACK);
    separator_14.setBounds(901, 0, 8, 103);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_14);
    
    JSeparator separator_15 = new JSeparator();
    separator_15.setOrientation(SwingConstants.VERTICAL);
    separator_15.setForeground(Color.BLACK);
    separator_15.setBounds(900, 0, 8, 103);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_15);
    
    JSeparator separator_16 = new JSeparator();
    separator_16.setForeground(Color.BLACK);
    separator_16.setBounds(669, 346, 708, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_16);
    
    JSeparator separator_17 = new JSeparator();
    separator_17.setOrientation(SwingConstants.VERTICAL);
    separator_17.setForeground(Color.BLACK);
    separator_17.setBounds(1022, 102, 8, 246);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_17);
    
    JSeparator separator_18 = new JSeparator();
    separator_18.setForeground(Color.LIGHT_GRAY);
    separator_18.setBounds(204, 102, 468, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_18);
    
    JSeparator separator_19 = new JSeparator();
    separator_19.setOrientation(SwingConstants.VERTICAL);
    separator_19.setForeground(Color.BLACK);
    separator_19.setBounds(1131, 0, 8, 103);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_19);
    
    JSeparator separator_20 = new JSeparator();
    separator_20.setOrientation(SwingConstants.VERTICAL);
    separator_20.setForeground(Color.BLACK);
    separator_20.setBounds(1060, 46, 8, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_20);
    
    JSeparator separator_21 = new JSeparator();
    separator_21.setOrientation(SwingConstants.VERTICAL);
    separator_21.setForeground(Color.BLACK);
    separator_21.setBounds(1294, 46, 8, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_21);
    
    JSeparator separator_22 = new JSeparator();
    separator_22.setForeground(Color.DARK_GRAY);
    separator_22.setBounds(669, 140, 708, 2);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(separator_22);
    
    JLabel Motor_Temp = new JLabel("Motor Temperature");
    Motor_Temp.setFont(new Font("Arial", Font.PLAIN, 20));
    Motor_Temp.setBounds(118, 341, 171, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Motor_Temp);
    
    JLabel Vehicle_Tilt_Angle = new JLabel("Vehicle Tilt Angle");
    Vehicle_Tilt_Angle.setFont(new Font("Arial", Font.PLAIN, 20));
    Vehicle_Tilt_Angle.setBounds(462, 569, 151, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vehicle_Tilt_Angle);
    
    JLabel Vichele_Speed = new JLabel("Vichele Speed");
    Vichele_Speed.setFont(new Font("Arial", Font.PLAIN, 20));
    Vichele_Speed.setBounds(448, 341, 127, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vichele_Speed);
    
    JLabel Controller_Perentage = new JLabel("Controller Percentage");
    Controller_Perentage.setHorizontalAlignment(SwingConstants.CENTER);
    Controller_Perentage.setFont(new Font("Arial", Font.PLAIN, 20));
    Controller_Perentage.setBounds(93, 216, 216, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Controller_Perentage);
    
    JLabel Disable_or_enable_the_motor = new JLabel("Disable or enable the motor");
    Disable_or_enable_the_motor.setHorizontalAlignment(SwingConstants.CENTER);
    Disable_or_enable_the_motor.setFont(new Font("Arial", Font.PLAIN, 20));
    Disable_or_enable_the_motor.setBounds(390, 216, 250, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Disable_or_enable_the_motor);
    
    JLabel Actual_Motor_Percentage_Control = new JLabel("Actual Motor Percentage Control");
    Actual_Motor_Percentage_Control.setFont(new Font("Arial", Font.PLAIN, 20));
    Actual_Motor_Percentage_Control.setBounds(204, 463, 288, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Actual_Motor_Percentage_Control);

    JLabel Battery_Percentage = new JLabel("Battery percentage");
    Battery_Percentage.setHorizontalAlignment(SwingConstants.CENTER);
    Battery_Percentage.setFont(new Font("Arial", Font.PLAIN, 20));
    Battery_Percentage.setBounds(689, 12, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Battery_Percentage);
    
    JLabel Mother_Board_Serial = new JLabel("Mother Board Serial");
    Mother_Board_Serial.setForeground(new Color(51, 204, 204));
    Mother_Board_Serial.setHorizontalAlignment(SwingConstants.CENTER);
    Mother_Board_Serial.setFont(new Font("Arial", Font.PLAIN, 20));
    Mother_Board_Serial.setBounds(750, 110, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Mother_Board_Serial);
    
    JLabel NXT_Serial = new JLabel("Xavier Serial");
    NXT_Serial.setForeground(new Color(51, 204, 204));
    NXT_Serial.setHorizontalAlignment(SwingConstants.CENTER);
    NXT_Serial.setFont(new Font("Arial", Font.PLAIN, 20));
    NXT_Serial.setBounds(1118, 110, 190, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(NXT_Serial);
    
    JLabel Rader = new JLabel("Rader");
    Rader.setHorizontalAlignment(SwingConstants.LEFT);
    Rader.setFont(new Font("Arial", Font.PLAIN, 20));
    Rader.setBounds(681, 350, 61, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Rader);
    
    JLabel Wheelchair_figure = new JLabel("");
    Wheelchair_figure.setToolTipText("Wheelchair");
    Wheelchair_figure.setIcon(new ImageIcon("D:\\AutoBrake\\Auto_Brake_ComputerSite_System_Code\\image\\wheelChair_TOP.png"));
    Wheelchair_figure.setBounds(1005, 456, 151, 131);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Wheelchair_figure);
    
    Motor_Temp_V = new JLabel("0\u00B0C");
    Motor_Temp_V.setToolTipText("The temperature renew per half second");
    Motor_Temp_V.setHorizontalAlignment(SwingConstants.CENTER);
    Motor_Temp_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Motor_Temp_V.setBounds(139, 375, 129, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Motor_Temp_V);

    Vichele_Tilt_Angle_V = new JLabel("0\u00B0");
    Vichele_Tilt_Angle_V.setToolTipText("Angle renew per 10 millisecond");
    Vichele_Tilt_Angle_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Tilt_Angle_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Tilt_Angle_V.setBounds(483, 603, 108, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vichele_Tilt_Angle_V);

    Vichele_Speed_V = new JLabel("0 km/hr");
    Vichele_Speed_V.setToolTipText("Speed Value renew immediately");
    Vichele_Speed_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Speed_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Speed_V.setBounds(405, 375, 219, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vichele_Speed_V);

    Controller_Perentage_V = new JLabel("0%");
    Controller_Perentage_V.setToolTipText("Controller percentage renew immediately");
    Controller_Perentage_V.setHorizontalAlignment(SwingConstants.CENTER);
    Controller_Perentage_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Controller_Perentage_V.setBounds(133, 250, 137, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Controller_Perentage_V);

    Battery_Percentage_V = new JLabel("0%");
    Battery_Percentage_V.setToolTipText("Battery percentage renew per minute when vehicle motor has no apply");
    Battery_Percentage_V.setHorizontalAlignment(SwingConstants.CENTER);
    Battery_Percentage_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Battery_Percentage_V.setBounds(716, 46, 137, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Battery_Percentage_V);

    Front_Brake_V = new JLabel("0 N");
    Front_Brake_V.setToolTipText("Front Brake Valuerenew immediately");
    Front_Brake_V.setHorizontalAlignment(SwingConstants.CENTER);
    Front_Brake_V.setForeground(new Color(0, 0, 0));
    Front_Brake_V.setFont(new Font("Arial", Font.PLAIN, 20));
    Front_Brake_V.setBounds(1062, 63, 69, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Front_Brake_V);

    Back_Brake_V = new JLabel("0 N");
    Back_Brake_V.setToolTipText("Back Brake Valuerenew immediately");
    Back_Brake_V.setHorizontalAlignment(SwingConstants.CENTER);
    Back_Brake_V.setForeground(Color.BLACK);
    Back_Brake_V.setFont(new Font("Arial", Font.PLAIN, 20));
    Back_Brake_V.setBounds(1296, 63, 69, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Back_Brake_V);
    
    JLabel UID_No = new JLabel("0000000000");
    UID_No.setToolTipText("The UID number of the user");
    UID_No.setForeground(Color.DARK_GRAY);
    UID_No.setHorizontalAlignment(SwingConstants.LEFT);
    UID_No.setFont(new Font("Consolas", Font.PLAIN, 28));
    UID_No.setBounds(284, 12, 190, 36);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(UID_No);
    
    Mother_Board_Serial_List = new List();
    Mother_Board_Serial_List.setMultipleSelections(false);
    Mother_Board_Serial_List.setFont(new Font("Arial", Font.PLAIN, 18));
    Mother_Board_Serial_List.setBounds(673, 140, 348, 165);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Mother_Board_Serial_List);
    
    NXT_Serial_List = new List();
    NXT_Serial_List.setMultipleSelections(false);
    NXT_Serial_List.setFont(new Font("Arial", Font.PLAIN, 18));
    NXT_Serial_List.setBounds(1026, 140, 348, 165);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(NXT_Serial_List);
    
    
    
// Interactive components

  //Motor
    Disable_or_enable_the_motor_Button = new JButton("ENABLE");
    Disable_or_enable_the_motor_Button.setEnabled(false);
    Disable_or_enable_the_motor_Button.setActionCommand("Tap to ENABLE");
    Disable_or_enable_the_motor_Button.setBackground(Color.GREEN);
    Disable_or_enable_the_motor_Button.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Disable_or_enable_the_motor_Button.setBounds(405, 262, 219, 43);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Disable_or_enable_the_motor_Button);
    
    Actual_Motor_Percentage_Control_Slider = new JSlider();
    Actual_Motor_Percentage_Control_Slider.setEnabled(false);
    Actual_Motor_Percentage_Control_Slider.setToolTipText("Slide the bar as the controller,REMEMBER to ENABLE the motor");
    Actual_Motor_Percentage_Control_Slider.setPaintLabels(true);
    Actual_Motor_Percentage_Control_Slider.setSnapToTicks(true);
    Actual_Motor_Percentage_Control_Slider.setBackground(Color.WHITE);
    Actual_Motor_Percentage_Control_Slider.setForeground(Color.GREEN);
    Actual_Motor_Percentage_Control_Slider.setValue(0);
    Actual_Motor_Percentage_Control_Slider.setBounds(21, 505, 644, 48);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Actual_Motor_Percentage_Control_Slider);
    
  //Connection
    COM_selection_comboBox = new JComboBox<String>();
    COM_selection_comboBox.setBackground(Color.WHITE);
    COM_selection_comboBox.setFont(new Font("Arial Rounded MT Bold", Font.PLAIN, 23));
    COM_selection_comboBox.setToolTipText("Choose Mother Board COM number");
    COM_selection_comboBox.setBounds(379, 58, 151, 34);
    SerialPort[] portNames = SerialPort.getCommPorts();
    for(int i = 0; i < portNames.length; i++) COM_selection_comboBox.addItem(portNames[i].getSystemPortName());
    frmMsbaautobrakecomputersitesystem.getContentPane().add(COM_selection_comboBox);
    
    JButton Dis_Connect = new JButton("Connect");
    Dis_Connect.setForeground(Color.BLACK);
    Dis_Connect.setBackground(Color.WHITE);
    Dis_Connect.setBounds(536, 58, 123, 34);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Dis_Connect);
    
  //Mother Board Serial
    JFormattedTextField Mother_Board_Serial_TextBox = new JFormattedTextField();
    Mother_Board_Serial_TextBox.setEnabled(false);
    Mother_Board_Serial_TextBox.setToolTipText("<English only>  \r\nType here to send message to Mother Board via Serial");
    Mother_Board_Serial_TextBox.setFont(new Font("Constantia", Font.PLAIN, 14));
    Mother_Board_Serial_TextBox.setBounds(671, 307, 277, 38);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Mother_Board_Serial_TextBox);
    
    Button Mother_Board_Serial_SendButton = new Button("Send");
    Mother_Board_Serial_SendButton.setEnabled(false);
    Mother_Board_Serial_SendButton.setBounds(946, 307, 76, 38);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Mother_Board_Serial_SendButton);
    
  //NXT Serial
    JFormattedTextField NXT_Serial_TextBox = new JFormattedTextField();
    NXT_Serial_TextBox.setEnabled(false);
    NXT_Serial_TextBox.setToolTipText("<English only>  \r\nType here to send message to NXT via Serial");
    NXT_Serial_TextBox.setFont(new Font("Constantia", Font.PLAIN, 14));
    NXT_Serial_TextBox.setBounds(1024, 307, 277, 38);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(NXT_Serial_TextBox);
    
    Button NXT_Serial_SendButton = new Button("Send");
    NXT_Serial_SendButton.setEnabled(false);
    NXT_Serial_SendButton.setBounds(1298, 307, 76, 38);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(NXT_Serial_SendButton);

  //Front Brake
    Front_Brake_Slider = new JSlider();
    Front_Brake_Slider.setEnabled(false);
    Front_Brake_Slider.setToolTipText("Slide to controller FRONT brake");
    Front_Brake_Slider.setBackground(Color.WHITE);
    Front_Brake_Slider.setForeground(Color.WHITE);
    Front_Brake_Slider.setSnapToTicks(true);
    Front_Brake_Slider.setPaintLabels(true);
    Front_Brake_Slider.setValue(0);
    Front_Brake_Slider.setBounds(903, 62, 156, 26);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Front_Brake_Slider);
    
  //Back Brake
    Back_Brake_Slider = new JSlider();
    Back_Brake_Slider.setEnabled(false);
    Back_Brake_Slider.setToolTipText("Slide to controller BACK brake");
    Back_Brake_Slider.setBackground(Color.WHITE);
    Back_Brake_Slider.setForeground(Color.WHITE);
    Back_Brake_Slider.setValue(0);
    Back_Brake_Slider.setSnapToTicks(true);
    Back_Brake_Slider.setPaintLabels(true);
    Back_Brake_Slider.setBounds(1134, 62, 159, 26);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Back_Brake_Slider);
    
  //Logout
    Button Logout_Button = new Button("Log Out");
    Logout_Button.setBounds(583, 13, 76, 23);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Logout_Button);
    
    distance_sensor_R_1= new JLabel("\u25E3");
    distance_sensor_R_1.setForeground(Color.WHITE);
    distance_sensor_R_1.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_R_1.setBounds(1157, 574, 107, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_1);
    
    distance_sensor_R_2 = new JLabel("\u258D");
    distance_sensor_R_2.setForeground(Color.WHITE);
    distance_sensor_R_2.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_R_2.setBounds(1119, 574, 129, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_2);
    
    distance_sensor_R_3 = new JLabel("\u2589");
    distance_sensor_R_3.setForeground(Color.WHITE);
    distance_sensor_R_3.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_R_3.setBounds(1037, 574, 181, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_3);

    distance_sensor_R_4 = new JLabel("\u258D");
    distance_sensor_R_4.setForeground(Color.WHITE);
    distance_sensor_R_4.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_R_4.setBounds(998, 574, 233, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_4);
    
    distance_sensor_R_5 = new JLabel("\u25E2");
    distance_sensor_R_5.setForeground(Color.WHITE);
    distance_sensor_R_5.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_R_5.setBounds(903, 574, 280, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_5);
    
    distance_sensor_L_1 = new JLabel("\u25E4");
    distance_sensor_L_1.setForeground(Color.WHITE);
    distance_sensor_L_1.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_L_1.setBounds(1157, 347, 107, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_1);
    
    distance_sensor_L_2 = new JLabel("\u258D");
    distance_sensor_L_2.setForeground(Color.WHITE);
    distance_sensor_L_2.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_L_2.setBounds(1119, 347, 129, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_2);
    
    distance_sensor_L_3 = new JLabel("\u2589");
    distance_sensor_L_3.setForeground(Color.WHITE);
    distance_sensor_L_3.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_L_3.setBounds(1037, 347, 181, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_3);
    
    distance_sensor_L_4 = new JLabel("\u258D");
    distance_sensor_L_4.setForeground(Color.WHITE);
    distance_sensor_L_4.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_L_4.setBounds(998, 347, 233, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_4);
    
    distance_sensor_L_5 = new JLabel("\u25E5");
    distance_sensor_L_5.setForeground(Color.WHITE);
    distance_sensor_L_5.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_L_5.setBounds(903, 347, 280, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_5);
    
    distance_sensor_B_R = new JLabel("\u25E4");
    distance_sensor_B_R.setForeground(Color.WHITE);
    distance_sensor_B_R.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_B_R.setBounds(901, 554, 107, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_R);
    
    distance_sensor_B_L = new JLabel("\u25E3");
    distance_sensor_B_L.setForeground(Color.WHITE);
    distance_sensor_B_L.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_B_L.setBounds(901, 375, 107, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_L);

    distance_sensor_B_M = new JLabel("\u2587");
    distance_sensor_B_M.setForeground(Color.WHITE);
    distance_sensor_B_M.setFont(new Font("Dialog", Font.PLAIN, 90));
    distance_sensor_B_M.setBounds(901, 459, 181, 122);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_M);
    
    distance_sensor_R_5_V = new JLabel("00.00");
    distance_sensor_R_5_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_R_5_V.setForeground(Color.BLACK);
    distance_sensor_R_5_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_R_5_V.setBounds(921, 681, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_5_V);
    
    distance_sensor_R_4_V = new JLabel("00.00");
    distance_sensor_R_4_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_R_4_V.setForeground(Color.BLACK);
    distance_sensor_R_4_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_R_4_V.setBounds(986, 681, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_4_V);
    
    distance_sensor_R_3_V = new JLabel("00.00");
    distance_sensor_R_3_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_R_3_V.setForeground(Color.BLACK);
    distance_sensor_R_3_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_R_3_V.setBounds(1047, 681, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_3_V);
    
    distance_sensor_R_2_V = new JLabel("00.00");
    distance_sensor_R_2_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_R_2_V.setForeground(Color.BLACK);
    distance_sensor_R_2_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_R_2_V.setBounds(1106, 681, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_2_V);
    
    distance_sensor_R_1_V = new JLabel("00.00");
    distance_sensor_R_1_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_R_1_V.setForeground(Color.BLACK);
    distance_sensor_R_1_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_R_1_V.setBounds(1167, 681, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_R_1_V);
    
    distance_sensor_L_5_V = new JLabel("00.00");
    distance_sensor_L_5_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_L_5_V.setForeground(Color.BLACK);
    distance_sensor_L_5_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_L_5_V.setBounds(921, 346, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_5_V);
    
    distance_sensor_L_4_V = new JLabel("00.00");
    distance_sensor_L_4_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_L_4_V.setForeground(Color.BLACK);
    distance_sensor_L_4_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_L_4_V.setBounds(986, 346, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_4_V);
    
    distance_sensor_L_3_V = new JLabel("00.00");
    distance_sensor_L_3_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_L_3_V.setForeground(Color.BLACK);
    distance_sensor_L_3_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_L_3_V.setBounds(1047, 346, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_3_V);
    
    distance_sensor_L_2_V = new JLabel("00.00");
    distance_sensor_L_2_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_L_2_V.setForeground(Color.BLACK);
    distance_sensor_L_2_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_L_2_V.setBounds(1106, 346, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_2_V);
    
    distance_sensor_L_1_V = new JLabel("00.00");
    distance_sensor_L_1_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_L_1_V.setForeground(Color.BLACK);
    distance_sensor_L_1_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_L_1_V.setBounds(1167, 346, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_L_1_V);
    
    distance_sensor_B_L_V = new JLabel("00.00");
    distance_sensor_B_L_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_B_L_V.setForeground(Color.BLACK);
    distance_sensor_B_L_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_B_L_V.setBounds(832, 425, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_L_V);
    
    distance_sensor_B_M_V = new JLabel("00.00");
    distance_sensor_B_M_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_B_M_V.setForeground(Color.BLACK);
    distance_sensor_B_M_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_B_M_V.setBounds(830, 515, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_M_V);
    
    distance_sensor_B_R_V = new JLabel("00.00");
    distance_sensor_B_R_V.setHorizontalAlignment(SwingConstants.CENTER);
    distance_sensor_B_R_V.setForeground(Color.BLACK);
    distance_sensor_B_R_V.setFont(new Font("Dialog", Font.PLAIN, 13));
    distance_sensor_B_R_V.setBounds(832, 605, 61, 20);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(distance_sensor_B_R_V);
    
    JLabel Vehicle_Rise_Angle = new JLabel("Vehicle Rise Angle");
    Vehicle_Rise_Angle.setHorizontalAlignment(SwingConstants.CENTER);
    Vehicle_Rise_Angle.setFont(new Font("Arial", Font.PLAIN, 20));
    Vehicle_Rise_Angle.setBounds(260, 569, 174, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vehicle_Rise_Angle);
    
    JLabel Vehicle_Acc = new JLabel("Vehicle accelerate");
    Vehicle_Acc.setHorizontalAlignment(SwingConstants.CENTER);
    Vehicle_Acc.setFont(new Font("Arial", Font.PLAIN, 20));
    Vehicle_Acc.setBounds(45, 569, 174, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vehicle_Acc);
    
    Vichele_Rise_Angle_V = new JLabel("0\u00B0");
    Vichele_Rise_Angle_V.setToolTipText("Angle renew per 10 millisecond");
    Vichele_Rise_Angle_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Rise_Angle_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Rise_Angle_V.setBounds(292, 603, 108, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vichele_Rise_Angle_V);

    Vichele_Acc_V = new JLabel("0 m/s2");
    Vichele_Acc_V.setToolTipText("Angle renew per 10 millisecond");
    Vichele_Acc_V.setHorizontalAlignment(SwingConstants.CENTER);
    Vichele_Acc_V.setFont(new Font("Arial Black", Font.PLAIN, 35));
    Vichele_Acc_V.setBounds(55, 603, 164, 58);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Vichele_Acc_V);
    
    Rader_ON_OFF_Slide = new JSlider();
    Rader_ON_OFF_Slide.setEnabled(false);
    Rader_ON_OFF_Slide.setForeground(Color.WHITE);
    Rader_ON_OFF_Slide.setBackground(Color.WHITE);
    Rader_ON_OFF_Slide.setToolTipText("Turn on the rader may reduce the speed of  the renew rate");
    Rader_ON_OFF_Slide.setMaximum(1);
    Rader_ON_OFF_Slide.setValue(0);
    Rader_ON_OFF_Slide.setBounds(725, 375, 48, 26);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(Rader_ON_OFF_Slide);
    
    JLabel lblOnOff = new JLabel("OFF          ON");
    lblOnOff.setHorizontalAlignment(SwingConstants.LEFT);
    lblOnOff.setFont(new Font("Arial", Font.PLAIN, 20));
    lblOnOff.setBounds(679, 375, 145, 24);
    frmMsbaautobrakecomputersitesystem.getContentPane().add(lblOnOff);
    
    
    
    
//Listener
  //Connection
    Disable_or_enable_the_motor_Button.addActionListener(new ActionListener(){
      @Override 
      public void actionPerformed(ActionEvent arg0) {
        if(Disable_or_enable_the_motor_Button.getText().equals("ENABLE")) {
            Disable_or_enable_the_motor_Button.setBackground(Color.RED);
            Disable_or_enable_the_motor_Button.setText("DISABLE");
            Disable_or_enable_the_motor_Button.setActionCommand("Tap to DISABLE");
            SimpleDateFormat time = new SimpleDateFormat("yyyy,MM,dd HH:mm:ss.SSS");
            Date current = new Date();
            String send = "@"+ time.format(current) + " ";
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
    //-------------------------------------------------------------have to be edit--------------------------------------------------------------
    Rader_ON_OFF_Slide.addChangeListener(new ChangeListener() {
      public void stateChanged(ChangeEvent e) {
        JSlider source = (JSlider)e.getSource();
        if (!source.getValueIsAdjusting()) {
          int slide_on_off = (int)source.getValue();
          if (slide_on_off==0) {
              print("");
              distance_sensor_R_1_V.setText("00.00");
              distance_sensor_R_2_V.setText("00.00");
              distance_sensor_R_3_V.setText("00.00");
              distance_sensor_R_4_V.setText("00.00");
              distance_sensor_R_5_V.setText("00.00");
              distance_sensor_R_1.setForeground(Color.WHITE);
              distance_sensor_R_2.setForeground(Color.WHITE);
              distance_sensor_R_3.setForeground(Color.WHITE);
              distance_sensor_R_4.setForeground(Color.WHITE);
              distance_sensor_R_5.setForeground(Color.WHITE);
              distance_sensor_L_1_V.setText("00.00");
              distance_sensor_L_2_V.setText("00.00");
              distance_sensor_L_3_V.setText("00.00");
              distance_sensor_L_4_V.setText("00.00");
              distance_sensor_L_5_V.setText("00.00");
              distance_sensor_L_1.setForeground(Color.WHITE);
              distance_sensor_L_2.setForeground(Color.WHITE);
              distance_sensor_L_3.setForeground(Color.WHITE);
              distance_sensor_L_4.setForeground(Color.WHITE);
              distance_sensor_L_5.setForeground(Color.WHITE);
              distance_sensor_B_L_V.setText("00.00");
              distance_sensor_B_M_V.setText("00.00");
              distance_sensor_B_R_V.setText("00.00");
              distance_sensor_B_R.setForeground(Color.WHITE);
              distance_sensor_B_M.setForeground(Color.WHITE);
              distance_sensor_B_L.setForeground(Color.WHITE);
          }
          else if (slide_on_off==1) {
              print("");
          }
        }
      }
    });
    //-------------------------------------------------------------------------------------------------------------------------------
    
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
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e1) {
                // TODO Auto-generated catch block
                e1.printStackTrace();
            }
            print("?");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            print("$C ");
            Rader_ON_OFF_Slide.enable();
            Actual_Motor_Percentage_Control_Slider.enable();
            Front_Brake_Slider.enable();
            Back_Brake_Slider.enable();
            Disable_or_enable_the_motor_Button.enable();
            Mother_Board_Serial_SendButton.enable();
            NXT_Serial_SendButton.enable();
            NXT_Serial_TextBox.enable();
            Mother_Board_Serial_TextBox.enable();
          }
        }
        else {
          // disconnect from the serial port
          print("$D ");
          chosenPort.closePort();
          hasChoosePort = false;
          COM_selection_comboBox.setEnabled(true);
          Dis_Connect.setText("Connect");
          Mother_Board_ConditionLight.setForeground(Color.RED);
          NXT_ConditionLight.setForeground(Color.RED);
          CTRL_Board_ConditionLight.setForeground(Color.RED);
          Brake_F_ConditionLight.setForeground(Color.RED);
          Brake_B_ConditionLight.setForeground(Color.RED);
          Distance_F_ConditionLight.setForeground(Color.RED);
          Distance_L_ConditionLight.setForeground(Color.RED);
          Distance_R_ConditionLight.setForeground(Color.RED);
          Distance_B_ConditionLight.setForeground(Color.RED);
          Speed_Sensor_ConditionLight.setForeground(Color.RED);
          Heat_n_Gsensor__ConditionLight.setForeground(Color.RED);
          Motor_Temp_V.setText("0\u00B0C");
          Vichele_Tilt_Angle_V.setText("0\u00B0");;
          Vichele_Speed_V.setText("0 km/hr");;
          Controller_Perentage_V.setText("0%");
          Battery_Percentage_V.setText("0%");
          Front_Brake_V.setText("0 N");
          Back_Brake_V.setText("0 N");
          Disable_or_enable_the_motor_Button.setText("ENABLE");
          Disable_or_enable_the_motor_Button.setBackground(Color.GREEN);
          distance_sensor_R_1_V.setText("00.00");
          distance_sensor_R_2_V.setText("00.00");
          distance_sensor_R_3_V.setText("00.00");
          distance_sensor_R_4_V.setText("00.00");
          distance_sensor_R_5_V.setText("00.00");
          distance_sensor_R_1.setForeground(Color.WHITE);
          distance_sensor_R_2.setForeground(Color.WHITE);
          distance_sensor_R_3.setForeground(Color.WHITE);
          distance_sensor_R_4.setForeground(Color.WHITE);
          distance_sensor_R_5.setForeground(Color.WHITE);
          distance_sensor_L_1_V.setText("00.00");
          distance_sensor_L_2_V.setText("00.00");
          distance_sensor_L_3_V.setText("00.00");
          distance_sensor_L_4_V.setText("00.00");
          distance_sensor_L_5_V.setText("00.00");
          distance_sensor_L_1.setForeground(Color.WHITE);
          distance_sensor_L_2.setForeground(Color.WHITE);
          distance_sensor_L_3.setForeground(Color.WHITE);
          distance_sensor_L_4.setForeground(Color.WHITE);
          distance_sensor_L_5.setForeground(Color.WHITE);
          distance_sensor_B_L_V.setText("00.00");
          distance_sensor_B_M_V.setText("00.00");
          distance_sensor_B_R_V.setText("00.00");
          distance_sensor_B_R.setForeground(Color.WHITE);
          distance_sensor_B_M.setForeground(Color.WHITE);
          distance_sensor_B_L.setForeground(Color.WHITE);
          Rader_ON_OFF_Slide.setValue(0);
          Actual_Motor_Percentage_Control_Slider.setValue(0);
          Front_Brake_Slider.setValue(0);
          Back_Brake_Slider.setValue(0);
          Rader_ON_OFF_Slide.disable();
          Actual_Motor_Percentage_Control_Slider.disable();
          Front_Brake_Slider.disable();
          Back_Brake_Slider.disable();
          Disable_or_enable_the_motor_Button.disable();
          Mother_Board_Serial_SendButton.disable();
          NXT_Serial_SendButton.disable();
          NXT_Serial_TextBox.disable();
          Mother_Board_Serial_TextBox.disable();
          COM_selection_comboBox.removeAll();
          SerialPort[] portNames = SerialPort.getCommPorts();
          for(int i = 0; i < portNames.length; i++) COM_selection_comboBox.addItem(portNames[i].getSystemPortName());
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
    
    frmMsbaautobrakecomputersitesystem.setVisible(true);
  }
  
static class RemindTask extends TimerTask {
  public void run() {
    if (hasChoosePort) {
      readS();
//      readSC();
    }
  }
}

static void readSC() {
  @SuppressWarnings("resource")
  Scanner scannerS /*System*/ = new Scanner(System.in);
  if (scannerS.hasNext()) {
      String line = scannerS.nextLine();
      print(line);
  }
}






static void readS() {
  Scanner scannerSC/*Serial COMM*/ = new Scanner(chosenPort.getInputStream());
  if (scannerSC.hasNext()) {
    try {
      int inascii = scannerSC.next().charAt(0);
      char in = (char)inascii;
      System.out.print(in);
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
          int CSinascii = scannerSC.next().charAt(0);
          char CSin = (char)CSinascii;
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
              if (Heat_n_Gsensor__ConditionLight.getForeground()==Color.RED) {
                Heat_n_Gsensor__ConditionLight.setForeground(Color.GREEN);
                Heat_n_Gsensor__ConditionLight.setToolTipText("connected");
              }
              else {
                  Heat_n_Gsensor__ConditionLight.setForeground(Color.RED);
                  Heat_n_Gsensor__ConditionLight.setToolTipText("disconnect");
              }
              break;
            }
          }
        }
        case 'X':{
          int num = scannerSC.nextInt();
          Controller_Perentage_V.setText(num+"%");
          Actual_Motor_Percentage_Control_Slider.setValue(num);
          break;
        }
        case 'V':{
          int num = scannerSC.nextInt();
          double speed = num / 100.00;
          Vichele_Speed_V.setText(speed+" km/hr");
          break;
        }
        case 'T':{
          int num = scannerSC.nextInt();
          Motor_Temp_V.setText(num+"\u00B0C");
          break;
        }
        case 'G':{
          int num = scannerSC.nextInt();
          Vichele_Tilt_Angle_V.setText(num+"\u00B0");
          break;
        }
        case 'I':{
          int num = scannerSC.nextInt();
          Vichele_Rise_Angle_V.setText(num+"\u00B0");
          break;
        }
        case 'A':{
          int num = scannerSC.nextInt();
          Vichele_Acc_V.setText(num+"m/s2");
          break;
        }
        case 'B':{
          int num = scannerSC.nextInt();
          Battery_Percentage_V.setText(num+" %");
          break;
        }
        case 'E':{
          int num = scannerSC.nextInt();
          Front_Brake_V.setText(num+" N");
          Front_Brake_Slider.setValue(num);
          break;
        }
        case 'D':{
          int num = scannerSC.nextInt();
          Back_Brake_V.setText(num+" N");
          Back_Brake_Slider.setValue(num);
          break;
        }
        case 'H':{
          String MotherSerial = scannerSC.nextLine();
          Mother_Board_Serial_List.add(MotherSerial);
          break;
        }
        case 'N':{
          String NXTSerial =scannerSC.nextLine();
          NXT_Serial_List.add(NXTSerial);
          break;
        }
        //Front distance Sensor
        case 'F':{
          break;
        }
        //Left distance Sensor
        case 'L':{
          float L_1 = scannerSC.nextFloat();
          float L_2 = scannerSC.nextFloat();
          float L_3 = scannerSC.nextFloat();
          float L_4 = scannerSC.nextFloat();
          float L_5 = scannerSC.nextFloat();
          String L_1_S = ""+L_1;
          String L_2_S = ""+L_2;
          String L_3_S = ""+L_3;
          String L_4_S = ""+L_4;
          String L_5_S = ""+L_5;
          distance_sensor_L_1_V.setText(L_1_S);
          distance_sensor_L_2_V.setText(L_2_S);
          distance_sensor_L_3_V.setText(L_3_S);
          distance_sensor_L_4_V.setText(L_4_S);
          distance_sensor_L_5_V.setText(L_5_S);
          double L_1_Wd = L_1/1.96078431372549*5;
          double L_2_Wd = L_2/1.96078431372549*5;
          double L_3_Wd = L_3/1.96078431372549*5;
          double L_4_Wd = L_4/1.96078431372549*5;
          double L_5_Wd = L_5/1.96078431372549*5;
          int L_1_W = (int)L_1_Wd;
          int L_2_W = (int)L_2_Wd;
          int L_3_W = (int)L_3_Wd;
          int L_4_W = (int)L_4_Wd;
          int L_5_W = (int)L_5_Wd;
          if (L_1_W >255) L_1_W = 255;
          if (L_2_W >255) L_2_W = 255;
          if (L_3_W >255) L_3_W = 255;
          if (L_4_W >255) L_4_W = 255;
          if (L_5_W >255) L_5_W = 255;
          distance_sensor_L_1.setForeground(new Color(255,L_1_W,L_1_W));
          distance_sensor_L_2.setForeground(new Color(255,L_2_W,L_2_W));
          distance_sensor_L_3.setForeground(new Color(255,L_3_W,L_3_W));
          distance_sensor_L_4.setForeground(new Color(255,L_4_W,L_4_W));
          distance_sensor_L_5.setForeground(new Color(255,L_5_W,L_5_W));
          String line = "\t"+L_1+"\t"+L_2+"\t"+L_3+"\t"+L_4+"\t"+L_5;
          System.out.println(line);
          break;
        }
        //Back distance Sensor
        case 'C':{
          break;
        }
        //Right distance Sensor
        case 'R':{
          float R_1 = scannerSC.nextFloat();
          float R_2 = scannerSC.nextFloat();
          float R_3 = scannerSC.nextFloat();
          float R_4 = scannerSC.nextFloat();
          float R_5 = scannerSC.nextFloat();
          String R_1_S = ""+R_1;
          String R_2_S = ""+R_2;
          String R_3_S = ""+R_3;
          String R_4_S = ""+R_4;
          String R_5_S = ""+R_5;
          distance_sensor_R_1_V.setText(R_1_S);
          distance_sensor_R_2_V.setText(R_2_S);
          distance_sensor_R_3_V.setText(R_3_S);
          distance_sensor_R_4_V.setText(R_4_S);
          distance_sensor_R_5_V.setText(R_5_S);
          double R_1_Wd = R_1/1.96078431372549*5;
          double R_2_Wd = R_2/1.96078431372549*5;
          double R_3_Wd = R_3/1.96078431372549*5;
          double R_4_Wd = R_4/1.96078431372549*5;
          double R_5_Wd = R_5/1.96078431372549*5;
          int R_1_W = (int)R_1_Wd;
          int R_2_W = (int)R_2_Wd;
          int R_3_W = (int)R_3_Wd;
          int R_4_W = (int)R_4_Wd;
          int R_5_W = (int)R_5_Wd;
          if (R_1_W >255) R_1_W = 255;
          if (R_2_W >255) R_2_W = 255;
          if (R_3_W >255) R_3_W = 255;
          if (R_4_W >255) R_4_W = 255;
          if (R_5_W >255) R_5_W = 255;
          distance_sensor_R_1.setForeground(new Color(255,R_1_W,R_1_W));
          distance_sensor_R_2.setForeground(new Color(255,R_2_W,R_2_W));
          distance_sensor_R_3.setForeground(new Color(255,R_3_W,R_3_W));
          distance_sensor_R_4.setForeground(new Color(255,R_4_W,R_4_W));
          distance_sensor_R_5.setForeground(new Color(255,R_5_W,R_5_W));
          String line = "\t"+R_1+"\t"+R_2+"\t"+R_3+"\t"+R_4+"\t"+R_5;
          System.out.println(line);
          break;
        }
      }
        frmMsbaautobrakecomputersitesystem.repaint();
    }
    catch(Exception e) {}
  }
  scannerSC.close();
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