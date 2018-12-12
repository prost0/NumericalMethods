package main;

import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.Initializable;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;

import libnm.math.Matrix;
import libnm.math.Vector;
import libnm.math.expression.ExpTree;
import libnm.math.pde.Hyperbolic;
import libnm.util.Logger;
import libnm.util.Reader;

public class MainController implements Initializable {
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		method = new Hyperbolic();
		matU = new Matrix();
		vecX = new Vector();
		vecT = new Vector();

		scrollBarK.valueProperty().addListener(new ChangeListener<Number>() {
			@Override
			public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
				int k = newValue.intValue();

				labelK.setText("Параметры графика (k = " + k + ")");

				updatePlotters(k);
			}
		});

		if (new File("input.txt").exists()) {
			Reader reader = new Reader("input.txt");

//			fieldA.setText(reader.readLine());
//			fieldB.setText(reader.readLine());
//			fieldC.setText(reader.readLine());
//			fieldE.setText(reader.readLine());
//			fieldExprF.setText(reader.readLine());
			fieldA.setText("1");
			fieldB.setText("0");
			fieldC.setText("-5");
			fieldE.setText("0");
			fieldExprF.setText("0");
//			fieldExprPsi1.setText(reader.readLine());
//			fieldExprPsi2.setText(reader.readLine());
//			fieldExprPsi1.setText("e^(2*x)");
//			fieldExprPsi2.setText("0");
//			fieldAlpha.setText("1");
//			fieldBeta.setText("-2");
//			fieldGamma.setText("1");
//			fieldDelta.setText("-2");
//			fieldExprFi0.setText("0");
//			fieldExprFi1.setText("0");
//			fieldL.setText("1");
//			fieldK.setText(reader.readLine());
//			fieldTau.setText(reader.readLine());
//			fieldN.setText(reader.readLine());
//			fieldExprU.setText("e^(2*x)*cos(t)");


			reader.close();
		}
	}

	public void buttonSolve(ActionEvent actionEvent) {
		int scheme;
		int boundCond;
		int startCond;
		Logger output = new Logger("output.txt");
		RadioButton rbScheme = (RadioButton)rbGroupScheme.getSelectedToggle();
		RadioButton rbBoundCond = (RadioButton)rbGroupBoundCond.getSelectedToggle();
		RadioButton rbStartCond = (RadioButton)rbGroupStartCond.getSelectedToggle();

		if (rbScheme == radioButtonExplicit) {
			scheme = Hyperbolic.SCHEME_EXPLICIT;
		} else {
			scheme = Hyperbolic.SCHEME_IMPLICIT;
		}

		if (rbBoundCond == radioButtonBoundCond21) {
			boundCond = Hyperbolic.BOUNDARY_CONDITION_2_1;
		} else if (rbBoundCond == radioButtonBoundCond32) {
			boundCond = Hyperbolic.BOUNDARY_CONDITION_3_2;
		} else {
			boundCond = Hyperbolic.BOUNDARY_CONDITION_2_2;
		}

		if (rbStartCond == radioButtonStartCond1) {
			startCond = Hyperbolic.INITIAL_CONDITION_1;
		} else {
			startCond = Hyperbolic.INITIAL_CONDITION_2;
		}
//
//		method.setA(Double.parseDouble("1"));
//		method.setB(Double.parseDouble("0"));
//		method.setC(Double.parseDouble("-5"));
//		method.setE(Double.parseDouble("0"));
//		method.setExprF(new ExpTree("0"));
//		method.setExprPsi1(new ExpTree("e^(2*x)"));
//		method.setExprPsi2(new ExpTree("0"));
//		method.setAlpha(Double.parseDouble("1"));
//		method.setBeta(Double.parseDouble("-2"));
//		method.setGamma(Double.parseDouble("1"));
//		method.setDelta(Double.parseDouble("-2"));
//		method.setExprFi0(new ExpTree("0"));
//		method.setExprFi1(new ExpTree("0"));
//		method.setL(Double.parseDouble("1"));
//		method.setK(Integer.parseInt(fieldK.getText()));
//		method.setTau(Double.parseDouble(fieldTau.getText()));
//		method.setN(Integer.parseInt(fieldN.getText()));
//		method.setExprU(new ExpTree("e^(2*x)*cos(t)"));
//
//		sigma.setText(Double.toString(Math.pow(Double.parseDouble(fieldTau.getText()), 2) / Math.pow((1.0 / Integer.parseInt(fieldN.getText())), 2)));


		method.setA(Double.parseDouble("1"));
		method.setB(Double.parseDouble("0"));
		method.setC(Double.parseDouble("-3"));
		method.setE(Double.parseDouble("0"));
		method.setExprF(new ExpTree("0"));
		method.setExprPsi1(new ExpTree("0"));
		method.setExprPsi2(new ExpTree("2*cos(x)"));
		method.setAlpha(Double.parseDouble("0"));
		method.setBeta(Double.parseDouble("1"));
		method.setGamma(Double.parseDouble("0"));
		method.setDelta(Double.parseDouble("1"));
		method.setExprFi0(new ExpTree("sin(2*t)"));
		method.setExprFi1(new ExpTree("-sin(2*t)"));
		method.setL(Double.parseDouble("3.1415926535"));
		method.setK(Integer.parseInt(fieldK.getText()));
		method.setTau(Double.parseDouble(fieldTau.getText()));
		method.setN(Integer.parseInt(fieldN.getText()));
		method.setExprU(new ExpTree("cos(x)*sin(2*t)"));

		sigma.setText(Double.toString(Math.pow(Double.parseDouble(fieldTau.getText()), 2) / Math.pow((3.1415926535 / Integer.parseInt(fieldN.getText())), 2)));


		method.solve(scheme, boundCond, startCond, matU, vecX, vecT);

		output.writeln(matU.toString());
		output.close();

		scrollBarK.setMax(Double.parseDouble(fieldK.getText()));

		initPlotters();
		updatePlotters(0);
	}

	private void initPlotters() {
		seriesAnalytical = new XYChart.Series<>();
		seriesNumerical = new XYChart.Series<>();
		seriesError = new XYChart.Series<>();
		seriesAnalytical.setName("Анал.");
		seriesNumerical.setName("Числ.");
		seriesError.setName("e(t)");

		for (int j = 0; j < vecX.getSize(); ++j) {
			seriesAnalytical.getData().add(new XYChart.Data<>(0.0, 0.0));
			seriesNumerical.getData().add(new XYChart.Data<>(0.0, 0.0));
		}

		for (int i = 0; i < matU.getM(); ++i) {
			double error = 0.0;

			for (int j = 0; j < matU.getN(); ++j) {
				error = Math.max(error, Math.abs(matU.get(i, j) - method.u(vecX.get(j), vecT.get(i))));
			}

			seriesError.getData().add(new XYChart.Data<>(vecT.get(i), error));
		}

		plotterSolution.setCreateSymbols(false);
		plotterSolution.getData().clear();
		plotterSolution.getData().add(seriesAnalytical);
		plotterSolution.getData().add(seriesNumerical);

		plotterError.setCreateSymbols(false);
		plotterError.getData().clear();
		plotterError.getData().add(seriesError);
	}

	private void updatePlotters(int k) {
		for (int j = 0; j < vecX.getSize(); ++j) {
			seriesAnalytical.getData().set(j, new XYChart.Data<>(vecX.get(j), method.u(vecX.get(j), vecT.get(k))));
			seriesNumerical.getData().set(j, new XYChart.Data<>(vecX.get(j), matU.get(k, j)));
		}
	}

	private Hyperbolic method;
	private Matrix matU;
	private Vector vecX;
	private Vector vecT;
	private XYChart.Series<Double, Double> seriesAnalytical;
	private XYChart.Series<Double, Double> seriesNumerical;
	private XYChart.Series<Double, Double> seriesError;

	@FXML
	private TextField sigma;
	@FXML
	private LineChart<Double, Double> plotterSolution;
	@FXML
	private LineChart<Double, Double> plotterError;
	@FXML
	private TextField fieldA;
	@FXML
	private TextField fieldB;
	@FXML
	private TextField fieldC;
	@FXML
	private TextField fieldE;
	@FXML
	private TextField fieldExprF;
	@FXML
	private TextField fieldAlpha;
	@FXML
	private TextField fieldBeta;
	@FXML
	private TextField fieldGamma;
	@FXML
	private TextField fieldDelta;
	@FXML
	private TextField fieldExprFi0;
	@FXML
	private TextField fieldExprFi1;
	@FXML
	private TextField fieldL;
	@FXML
	private TextField fieldExprPsi1;
	@FXML
	private TextField fieldExprPsi2;
	@FXML
	private TextField fieldK;
	@FXML
	private TextField fieldTau;
	@FXML
	private TextField fieldN;
	@FXML
	private TextField fieldExprU;
	@FXML
	private ToggleGroup rbGroupScheme;
	@FXML
	private ToggleGroup rbGroupBoundCond;
	@FXML
	private ToggleGroup rbGroupStartCond;
	@FXML
	private RadioButton radioButtonExplicit;
	@FXML
	private RadioButton radioButtonBoundCond21;
	@FXML
	private RadioButton radioButtonBoundCond32;
	@FXML
	private RadioButton radioButtonStartCond1;
	@FXML
	private Label labelK;
	@FXML
	private ScrollBar scrollBarK;
}
