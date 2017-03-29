/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package amy_gui;

import java.io.File;
import javafx.application.Application;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.Orientation;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.Separator;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;

import org.zeromq.ZMQ;

/**
 *
 * @author oriol
 */
public class Amy_gui extends Application {
    ZMQ.Context context = ZMQ.context(1);
    
    //  Socket to SEND Commands
    ZMQ.Socket reqControlPRT = context.socket(ZMQ.REQ);
    ZMQ.Socket reqControlJoints = context.socket(ZMQ.REQ);
    
    //Socket to RECEIVE Feedback
    ZMQ.Socket repFbPRT = context.socket(ZMQ.REP);
    ZMQ.Socket repFbJoints = context.socket(ZMQ.REP);
    
    @Override
    public void start(Stage primaryStage) {
                
        /*
        PANE TOP LEFT -> CONTROL PAN & RADIUS & TILT
        COMS -> JEROMQ Server port 5401
        */
        
        reqControlPRT.connect("tcp://*:5401");
        reqControlPRT.setReceiveTimeOut(5000);
        
        final Label titleLabel = new Label(" Control Panel          ");
        titleLabel.setFont(Font.font("Arial", FontWeight.BOLD, 16));
        final Label panLabel = new Label("Pan");
        panLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        final Label tiltLabel = new Label("Tilt");
        tiltLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        tiltLabel.setRotate(270);
        final Label radiusLabel = new Label("Radius");
        radiusLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        
        final Slider radiusControl = new Slider();
        final Slider tiltControl = new Slider();
        final Slider panControl = new Slider();
        
        /*
        PANE TOP RIGHT -> FEEDBACK PAN & RADIUS & TILT
        COMS -> JEROMQ client port 5403
        */
        repFbPRT.bind("tcp://*:5403");
        
        final Label titleFbLabel = new Label(" Feedback Panel          ");
        titleFbLabel.setFont(Font.font("Arial", FontWeight.BOLD, 16));
        titleFbLabel.setTextFill(Color.rgb(135, 135, 135));
        
        final Label panFbLabel = new Label("Pan");
        panFbLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        panFbLabel.setTextFill(Color.rgb(135, 135, 135));
        final Label tiltFbLabel = new Label("Tilt");
        tiltFbLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        tiltFbLabel.setRotate(270);
        tiltFbLabel.setTextFill(Color.rgb(135, 135, 135));
        final Label radiusFbLabel = new Label("Radius");
        radiusFbLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        radiusFbLabel.setTextFill(Color.rgb(135, 135, 135));
        
        final Slider radiusFb = new Slider();
        radiusFb.setDisable(true);
        final Slider tiltFb = new Slider();
        tiltFb.setDisable(true);
        final Slider panFb = new Slider();
        panFb.setDisable(true);
        
        /*
        PANE BOTTOM LEFT -> CONTROL & FEEDBACK JOINTS
        COMS -> JEROMQ Server port 5405
                JEROMQ Client port 5407
        */
        reqControlJoints.bind("tcp://*:5405");
        repFbJoints.bind("tcp://*:5407");
        
        final Label titleJointsLabel = new Label(" JOINTS                     "
                                                +"                            ");
        titleJointsLabel.setFont(Font.font("Arial", FontWeight.BOLD, 16));
        
        final Label HSLabel = new Label("         HS -> ");
        HSLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        final Label VSLabel = new Label("         VS -> ");
        VSLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        final Label ELLabel = new Label("         EL -> ");
        ELLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        final Label HWLabel = new Label("        HW -> ");
        HWLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        final Label VWLabel = new Label("        VW -> ");
        VWLabel.setFont(Font.font("Arial", FontWeight.NORMAL, 12));
        
        final Slider HSFb = new Slider();
        HSFb.setDisable(true);
        final Slider VSFb = new Slider();
        VSFb.setDisable(true);
        final Slider ELFb = new Slider();
        ELFb.setDisable(true);
        final Slider HWFb = new Slider();
        HWFb.setDisable(true);
        final Slider VWFb = new Slider();
        VWFb.setDisable(true);
        
        final TextField HSTextfield = new TextField();
        HSTextfield.setPrefColumnCount(10);
        final TextField VSTextfield = new TextField();
        VSTextfield.setPrefColumnCount(10);
        final TextField ELTextfield = new TextField();
        ELTextfield.setPrefColumnCount(10);
        final TextField HWTextfield = new TextField();
        HWTextfield.setPrefColumnCount(10);
        final TextField VWTextfield = new TextField();
        VWTextfield.setPrefColumnCount(10);
        
        /*
        PANE BOTTOM RIGHT -> IMAGE UR5
        */
        File file = new File("/home/oriol/Pictures/ur5.png");
        Image image = new Image(file.toURI().toString());
        ImageView imageView = new ImageView(image);
        
        HBox hboxTop = new HBox(0);
        hboxTop.setTranslateX(0);
        hboxTop.setTranslateY(0);
        
        HBox hboxBottom = new HBox(0);
        hboxBottom.setTranslateX(0);
        hboxBottom.setTranslateY(0);
 
        /*
        TOP LEFT PANE -> Control Arm Pane 
        */
        FlowPane Pane1 = new FlowPane();
        Pane1.setPrefSize(360, 240);
        Pane1.setStyle("-fx-background-color: rgb(154,154,154)");
        Pane1.getChildren().add(titleLabel);
        Pane1.getChildren().add(radiusLabel);
        Pane1.getChildren().add(radiusControl);
        Pane1.getChildren().add(tiltLabel);
        Pane1.getChildren().add(tiltControl);
        Pane1.getChildren().add(panControl);
        Pane1.getChildren().add(panLabel);
        hboxTop.getChildren().add(Pane1);
        
        radiusControl.setLayoutX(0);
        radiusControl.setLayoutY(0);
        radiusControl.setTranslateX(Pane1.getPrefWidth()/2+2.5);
        radiusControl.setTranslateY(5-60);
        radiusControl.setOrientation(Orientation.HORIZONTAL);
        //radiusControl.setPrefHeight(5);
        radiusControl.setPrefWidth(Pane1.getPrefWidth()/2 -10);
        radiusControl.setMin(0);
        radiusControl.setValue(0);
        radiusControl.setMax(300);
        radiusControl.setShowTickLabels(true);
        radiusControl.setShowTickMarks(true);
        radiusControl.setMajorTickUnit(60);
        radiusControl.setMinorTickCount(5);
        radiusControl.setBlockIncrement(5);
        /*radiusControl.valueChangingProperty().addListener(new ChangeListener<Boolean>() {
            @Override
            public void changed(ObservableValue<? extends Boolean> observable, 

            }
            
        });*/
        radiusControl.setOnDragDetected(mouseEvent -> radiusControl.startFullDrag());
        radiusControl.setOnMouseDragReleased(new EventHandler<MouseDragEvent>() {
            @Override
            public void handle(MouseDragEvent event) { 
                
                    String valueString = String.format("%1$.3f", radiusControl.getValue());
                    System.out.format(valueString);
                    boolean send = reqControlPRT.send(valueString, 0);
                    System.out.format("Sending Control REQ -> "+valueString);
                     
                    byte[] responseBytes = reqControlPRT.recv(0);
                    String response = new String(responseBytes); 
                    System.out.format(response);
            }
        });
        radiusLabel.setTranslateY(17.5);
        radiusLabel.setTranslateX(-50);
        
        tiltControl.setLayoutX(0);
        tiltControl.setLayoutY(0);
        tiltControl.setTranslateX(0);
        tiltControl.setTranslateY(25);
        tiltControl.setOrientation(Orientation.VERTICAL);
        tiltControl.setPrefHeight(Pane1.getPrefHeight()-100);
        tiltControl.setPrefWidth(5);
        tiltControl.setMin(0);
        tiltControl.setValue(0);
        tiltControl.setMax(300);
        tiltControl.setShowTickLabels(true);
        tiltControl.setShowTickMarks(true);
        tiltControl.setMajorTickUnit(60);
        tiltControl.setMinorTickCount(5);
        tiltControl.setBlockIncrement(5);
        
        tiltLabel.setTranslateX(-15);
        tiltLabel.setTranslateY(25);
        
        panControl.setLayoutX(0);
        panControl.setLayoutY(0);
        panControl.setTranslateX(25);
        panControl.setTranslateY(27.5);
        panControl.setOrientation(Orientation.HORIZONTAL);
        panControl.setPrefHeight(5);
        panControl.setPrefWidth(Pane1.getPrefWidth() - 50);
        panControl.setMin(0);
        panControl.setValue(0);
        panControl.setMax(360);
        panControl.setShowTickLabels(true);
        panControl.setShowTickMarks(true);
        panControl.setMajorTickUnit(60);
        panControl.setMinorTickCount(50);
        panControl.setBlockIncrement(5);
        
        panLabel.setTranslateX(-140);
        panLabel.setTranslateY(47.5);
        
        final Separator separatorV1 = new Separator();
        separatorV1.setMaxWidth(40);
        separatorV1.setOrientation(Orientation.VERTICAL);
        separatorV1.setHalignment(HPos.CENTER);
        hboxTop.getChildren().add(separatorV1);
        
        /*
        TOP RIGHT PANE -> Feedback Arm Pane
        */
        FlowPane Pane2 = new FlowPane();
        Pane2.setPrefSize(360, 240);
        Pane2.setStyle("-fx-background-color: rgb(211,211,211)");
        Pane2.getChildren().add(titleFbLabel);
        Pane2.getChildren().add(radiusFbLabel);
        Pane2.getChildren().add(radiusFb);
        Pane2.getChildren().add(tiltFbLabel);
        Pane2.getChildren().add(tiltFb);
        Pane2.getChildren().add(panFbLabel);
        Pane2.getChildren().add(panFb);
        hboxTop.getChildren().add(Pane2);
        
        radiusFb.setLayoutX(0);
        radiusFb.setLayoutY(0);
        radiusFb.setTranslateX(Pane2.getPrefWidth()/2-7.5);
        radiusFb.setTranslateY(5-60);
        radiusFb.setOrientation(Orientation.HORIZONTAL);
        radiusFb.setPrefHeight(5);
        radiusFb.setPrefWidth(Pane2.getPrefWidth()/2 -10);
        radiusFb.setMin(0);
        radiusFb.setValue(60);
        radiusFb.setMax(300);
        radiusFb.setShowTickLabels(true);
        radiusFb.setShowTickMarks(true);
        radiusFb.setMajorTickUnit(60);
        radiusFb.setMinorTickCount(50);
        radiusFb.setBlockIncrement(5);
        
        radiusFbLabel.setTranslateY(20);
        radiusFbLabel.setTranslateX(-80);
        
        tiltFb.setLayoutX(0);
        tiltFb.setLayoutY(0);
        tiltFb.setTranslateX(-10);
        tiltFb.setTranslateY(25);
        tiltFb.setOrientation(Orientation.VERTICAL);
        tiltFb.setPrefHeight(Pane1.getPrefHeight()-100);
        tiltFb.setPrefWidth(5);
        tiltFb.setMin(0);
        tiltFb.setValue(0);
        tiltFb.setMax(300);
        tiltFb.setShowTickLabels(true);
        tiltFb.setShowTickMarks(true);
        tiltFb.setMajorTickUnit(60);
        tiltFb.setMinorTickCount(50);
        tiltFb.setBlockIncrement(5);
        
        tiltFbLabel.setTranslateX(-22.5);
        tiltFbLabel.setTranslateY(25);
        
        panFb.setLayoutX(0);
        panFb.setLayoutY(0);
        panFb.setTranslateX(25);
        panFb.setTranslateY(27.5);
        panFb.setOrientation(Orientation.HORIZONTAL);
        panFb.setPrefHeight(5);
        panFb.setPrefWidth(Pane2.getPrefWidth() - 50);
        panFb.setMin(0);
        panFb.setValue(0);
        panFb.setMax(360);
        panFb.setShowTickLabels(true);
        panFb.setShowTickMarks(true);
        panFb.setMajorTickUnit(60);
        panFb.setMinorTickCount(50);
        panFb.setBlockIncrement(5);
        
        panFbLabel.setTranslateX(-35);
        panFbLabel.setTranslateY(140);
        
       
        
        /*
        BOTTOM LEFT PANE -> Control&Feedback JOINTS
        */
        FlowPane Pane3 = new FlowPane();
        Pane3.setPrefSize(360, 240);
        Pane3.setStyle("-fx-background-color: rgb(154,154,154)");
        Pane3.getChildren().add(titleJointsLabel);
        Pane3.getChildren().add(HSLabel);
        Pane3.getChildren().add(HSTextfield);
        Pane3.getChildren().add(HSFb);
        Pane3.getChildren().add(VSLabel);
        Pane3.getChildren().add(VSTextfield);
        Pane3.getChildren().add(VSFb);
        Pane3.getChildren().add(ELLabel);
        Pane3.getChildren().add(ELTextfield);
        Pane3.getChildren().add(ELFb);
        Pane3.getChildren().add(HWLabel);
        Pane3.getChildren().add(HWTextfield);
        Pane3.getChildren().add(HWFb);
        Pane3.getChildren().add(VWLabel);
        Pane3.getChildren().add(VWTextfield);
        Pane3.getChildren().add(VWFb);
        hboxBottom.getChildren().add(Pane3);
        
        HSFb.setTranslateY(5);
        HSFb.setTranslateX(20);
        HSFb.setPrefHeight(5);
        HSFb.setPrefWidth(Pane3.getPrefWidth()/2);
        HSFb.setMin(0);
        HSFb.setValue(0);
        HSFb.setMax(300);
        HSFb.setShowTickLabels(true);
        HSFb.setShowTickMarks(true);
        HSFb.setMajorTickUnit(60);
        HSFb.setMinorTickCount(5);
        HSFb.setBlockIncrement(5);
        
        HSTextfield.setTranslateX(7.5);
        HSTextfield.setPrefWidth(60);
        
        VSFb.setTranslateY(5);
        VSFb.setTranslateX(20);
        VSFb.setPrefHeight(5);
        VSFb.setPrefWidth(Pane3.getPrefWidth()/2);
        VSFb.setMin(0);
        VSFb.setValue(0);
        VSFb.setMax(300);
        VSFb.setShowTickLabels(true);
        VSFb.setShowTickMarks(true);
        VSFb.setMajorTickUnit(60);
        VSFb.setMinorTickCount(5);
        VSFb.setBlockIncrement(5);
        
        VSTextfield.setTranslateX(7.5);
        VSTextfield.setPrefWidth(60);
        
        ELFb.setTranslateY(5);
        ELFb.setTranslateX(20);
        ELFb.setPrefHeight(5);
        ELFb.setPrefWidth(Pane3.getPrefWidth()/2);
        ELFb.setMin(0);
        ELFb.setValue(0);
        ELFb.setMax(300);
        ELFb.setShowTickLabels(true);
        ELFb.setShowTickMarks(true);
        ELFb.setMajorTickUnit(60);
        ELFb.setMinorTickCount(5);
        ELFb.setBlockIncrement(5);
        
        ELTextfield.setTranslateX(7.5);
        ELTextfield.setPrefWidth(60);
        
        HWFb.setTranslateY(5);
        HWFb.setTranslateX(20);
        HWFb.setPrefHeight(5);
        HWFb.setPrefWidth(Pane3.getPrefWidth()/2);
        HWFb.setMin(0);
        HWFb.setValue(0);
        HWFb.setMax(300);
        HWFb.setShowTickLabels(true);
        HWFb.setShowTickMarks(true);
        HWFb.setMajorTickUnit(60);
        HWFb.setMinorTickCount(5);
        HWFb.setBlockIncrement(5);
        
        HWTextfield.setTranslateX(7.5);
        HWTextfield.setPrefWidth(60);
        
        VWFb.setTranslateY(5);
        VWFb.setTranslateX(20);
        VWFb.setPrefHeight(5);
        VWFb.setPrefWidth(Pane3.getPrefWidth()/2);
        VWFb.setMin(0);
        VWFb.setValue(0);
        VWFb.setMax(300);
        VWFb.setShowTickLabels(true);
        VWFb.setShowTickMarks(true);
        VWFb.setMajorTickUnit(60);
        VWFb.setMinorTickCount(5);
        VWFb.setBlockIncrement(5);
        
        VWTextfield.setTranslateX(7.5);
        VWTextfield.setPrefWidth(60);
        
        final Separator separatorV2 = new Separator();
        separatorV2.setMaxWidth(40);
        separatorV2.setOrientation(Orientation.VERTICAL);
        separatorV2.setHalignment(HPos.CENTER);
        hboxBottom.getChildren().add(separatorV2);
        
        /*
        BOTTOM RIGHT PANE -> Control&Feedback JOINTS
        */
        FlowPane Pane4 = new FlowPane();
        Pane4.setPrefSize(360, 240);
        Pane4.getChildren().addAll(imageView);
        hboxBottom.getChildren().add(Pane4);
       
        imageView.setFitHeight(Pane4.getPrefHeight()-15);
        
        VBox VBox = new VBox();
        VBox.getChildren().add(hboxTop);
        
        final Separator separatorH = new Separator();
        separatorH.setMaxWidth(720);
        separatorH.setHalignment(HPos.CENTER);
        VBox.getChildren().add(separatorH);
        
        
        VBox.getChildren().add(hboxBottom);
        
        Scene scene = new Scene(new Group(VBox), 720, 480);
        primaryStage.setTitle("AMY");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
