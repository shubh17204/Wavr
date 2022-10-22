//
//  ServicesViewController.swift
//  Wavr
//
//  Created by Jass Chauhan on 8/9/22.
//

import Foundation
import UIKit

class ServicesViewController: UIViewController, UITableViewDelegate, BLEManagerDelegate {
    let tableView = UITableView()
    var bleManagerLocal: BLEManager!

    override func viewDidLoad() {
        super.viewDidLoad()
        bleManagerLocal = BLEManager(serviceUUID: wavrRightServiceUUID, delegate: self)
        setupTableView()
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    func setupTableView() {
        tableView.register(ServicesTableViewCell.self, forCellReuseIdentifier: "cell")
        tableView.dataSource = self
        tableView.delegate = self
        view.addSubview(tableView)
        tableView.translatesAutoresizingMaskIntoConstraints = false
        tableView.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 44).isActive = true
        tableView.leftAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leftAnchor).isActive = true
        tableView.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor).isActive = true
        tableView.rightAnchor.constraint(equalTo: view.safeAreaLayoutGuide.rightAnchor).isActive = true
    }
    
    func commManager(bleManager: BLEManager, didReceiveString recvdStr: String) {
        print(recvdStr)
    }
}

extension ServicesViewController: UITableViewDataSource {
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return availServices.count
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cell", for: indexPath) as! ServicesTableViewCell
        let textValue = availServices[indexPath.row].displayName
        cell.serviceLabel.text = textValue
        return cell
    }
    func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 48
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        bleManagerLocal.writeString(text: availServices[indexPath.row].serviceString)
    }
    
}

class ServicesTableViewCell: UITableViewCell {
    
    var serviceLabel = UILabel()
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    override init(style: UITableViewCell.CellStyle, reuseIdentifier: String?) {
        super.init(style: style, reuseIdentifier: reuseIdentifier)
        
        serviceLabel.font = UIFont.systemFont(ofSize: 15, weight: .medium)
        serviceLabel.translatesAutoresizingMaskIntoConstraints = false
        contentView.addSubview(serviceLabel)
        
        serviceLabel.topAnchor.constraint(equalTo: contentView.topAnchor).isActive = true
        serviceLabel.bottomAnchor.constraint(equalTo: contentView.bottomAnchor).isActive = true
        serviceLabel.leadingAnchor.constraint(equalTo: contentView.leadingAnchor, constant: 16).isActive = true
        serviceLabel.trailingAnchor.constraint(equalTo: contentView.trailingAnchor).isActive = true
    }
}

class availService {
    var displayName: String
    var serviceString: String
    
    init(displayName: String, serviceString: String) {
        self.displayName = displayName
        self.serviceString = serviceString
    }
}

let availServices: [availService] = [
    availService(displayName: "Ping", serviceString: "10"),
    availService(displayName: "Start Main Service", serviceString: "11"),
    availService(displayName: "Stop Main Service", serviceString: "12"),
    availService(displayName: "Restart Wavr", serviceString: "19"),
    
    availService(displayName: "Stop Haptics", serviceString: "20"),
    availService(displayName: "Start Haptics", serviceString: "21"),
    availService(displayName: "Play Haptic Chime - 'Start'", serviceString: "22"),
    availService(displayName: "Play Haptic Chime - 'Stop'", serviceString: "23"),
    availService(displayName: "Play Haptic Chime - 'Success'", serviceString: "24"),
    availService(displayName: "Play Haptic Chime - 'Error'", serviceString: "25"),
    
    availService(displayName: "Stop LED", serviceString: "30"),
    availService(displayName: "Set LED Red", serviceString: "31"),
    availService(displayName: "Set LED Green", serviceString: "32"),
    availService(displayName: "Set LED Blue", serviceString: "33"),
    availService(displayName: "Set LED Cyan", serviceString: "34"),
    availService(displayName: "Set LED Purple", serviceString: "35"),
    availService(displayName: "Set LED Yellow", serviceString: "36"),
    availService(displayName: "Set LED White", serviceString: "37"),
    
    availService(displayName: "Start Forced Calibration", serviceString: "40"),
    availService(displayName: "Start Conditional Calibration", serviceString: "41"),
    
    availService(displayName: "Request Characteristics", serviceString: "50"),
    availService(displayName: "Request Main Object", serviceString: "51"),
    availService(displayName: "Request Flex Object", serviceString: "52"),
    availService(displayName: "Request IMU Object", serviceString: "53"),
    availService(displayName: "Request Button Object", serviceString: "54"),
    availService(displayName: "Request Battery Estimate", serviceString: "55"),
    availService(displayName: "Request Parity Token", serviceString: "56"),
    availService(displayName: "Request LED-Haptic State", serviceString: "57"),
    
    availService(displayName: "Erase EEPROM", serviceString: "70"),
    availService(displayName: "Dump EEPROM", serviceString: "71"),
    
    availService(displayName: "Test Service", serviceString: "404")
]

