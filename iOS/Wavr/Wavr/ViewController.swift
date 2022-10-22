//
//  ViewController.swift
//  Wavr
//
//  Created by Jass Chauhan on 8/7/22.
//

import UIKit

class ViewController: UIViewController {
    var isConnectedToGloves: Bool = false
    
    var bleManagerLocal: BLEManager!
    var dataLabel: UILabel!
    var tokenSwitch: UISwitch!
    var calibrateButton: UIButton!
    
    var breakOutAngle: Int = 5
    
    var thumbAngle: Int = 0
    var indexAngle: Int = 0
    var middleAngle: Int = 0
    var ringAngle: Int = 0
    var fifthAngle: Int = 0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        bleManagerLocal = BLEManager(serviceUUID: wavrRightServiceUUID, delegate: self)
        
        tokenSwitch = UISwitch()
        tokenSwitch.addTarget(self, action: #selector(self.tokenSwitchChanged(_:)), for: .valueChanged)
        tokenSwitch.setOn(false, animated: false)
        self.view.addSubview(tokenSwitch)
        tokenSwitch.translatesAutoresizingMaskIntoConstraints = false
        tokenSwitch.widthAnchor.constraint(equalToConstant: 50).isActive = true
        tokenSwitch.heightAnchor.constraint(equalToConstant: 50).isActive = true
        tokenSwitch.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
        tokenSwitch.centerYAnchor.constraint(equalTo: view.centerYAnchor, constant: -100).isActive = true
        
        dataLabel = UILabel()
        dataLabel.text = "Waiting to connect"
        dataLabel.adjustsFontSizeToFitWidth = true
        view.addSubview(dataLabel)
        dataLabel.translatesAutoresizingMaskIntoConstraints = false
        dataLabel.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
        dataLabel.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
        dataLabel.heightAnchor.constraint(equalToConstant: 100).isActive = true
        dataLabel.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
        dataLabel.centerYAnchor.constraint(equalTo: view.centerYAnchor).isActive = true
        
        calibrateButton = UIButton()
        calibrateButton.setTitle("Calibrate", for: .normal)
        calibrateButton.addTarget(self, action: #selector(ReqCalibrate(_:)), for: .touchUpInside)
        view.addSubview(calibrateButton)
        calibrateButton.backgroundColor = .gray
        calibrateButton.layer.masksToBounds = true
        calibrateButton.layer.cornerRadius = 24
        calibrateButton.translatesAutoresizingMaskIntoConstraints = false
        calibrateButton.widthAnchor.constraint(equalToConstant: 100).isActive = true
        calibrateButton.heightAnchor.constraint(equalToConstant: 50).isActive = true
        calibrateButton.centerXAnchor.constraint(equalTo: view.centerXAnchor).isActive = true
        calibrateButton.centerYAnchor.constraint(equalTo: dataLabel.centerYAnchor, constant: +100).isActive = true
    }
    
    override func viewWillAppear(_ animated: Bool) {
        bleManagerLocal.requestService(service: .setMainBLEToken)
    }
    override func viewDidDisappear(_ animated: Bool) {
        bleManagerLocal.requestService(service: .removeMainBLEToken)
    }
    
    
    @objc func tokenSwitchChanged(_ sender:UISwitch!) {
            if (sender.isOn == true){
                bleManagerLocal.requestService(service: .setMainBLEToken)
                dataLabel.text = "Waiting for data"
            } else{
                bleManagerLocal.requestService(service: .removeMainBLEToken)
                dataLabel.text = "Data stream is off"
            }
    }
    
    @objc func ReqCalibrate(_ sender:UIButton!) {
        //bleManagerLocal.requestService(service: .forceCalib)
        bleManagerLocal.requestService(service: .restart)
    }
    
}

extension ViewController: BLEManagerDelegate {
    func commManager(bleManager: BLEManager, didReceiveString recvdStr: String) {
        isConnectedToGloves = true
        
        dataLabel.text = recvdStr
        
//
        
    }
}

