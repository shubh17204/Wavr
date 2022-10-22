//
//  BLE Manager.swift
//  Wavr
//
//  Created by Jass Chauhan on 8/7/22.
//

import CoreBluetooth

public let wavrRightServiceUUID: String = "0160667a-94f7-4b9e-a7e9-2523a4afe467"

protocol BLEManagerDelegate: AnyObject {
    func commManager(bleManager: BLEManager, didReceiveString recvdStr: String)
}

class BLEManager: NSObject {
    
    let serviceUUID: String
    weak var delegate: BLEManagerDelegate?
    
    var centralManager: CBCentralManager!
    var connectedPeripheral: CBPeripheral?
    var targetService: CBService?
    var writableCharacteristic: CBCharacteristic?
    
    init(serviceUUID: String, delegate: BLEManagerDelegate?) {
        self.serviceUUID = serviceUUID
        self.delegate = delegate
        
        super.init()
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
        
    func writeString(text: String) {
        guard let peripheral = connectedPeripheral, let characteristic = writableCharacteristic else {
            return
        }
            let data = text.data(using: .utf8)
            peripheral.writeValue(data!,  for: characteristic, type: CBCharacteristicWriteType.withResponse)
    }
    
    func requestService(service: Services) {
        guard let peripheral = connectedPeripheral, let characteristic = writableCharacteristic else {
            return
        }
        let data = service.rawValue.data(using: .utf8)
            peripheral.writeValue(data!,  for: characteristic, type: CBCharacteristicWriteType.withResponse)
    }
    
}

extension BLEManager: CBCentralManagerDelegate {
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        peripheral.discoverServices(nil)
        if let name = peripheral.name {
            print("Connected With \(name)")
        }
    }
    
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        connectedPeripheral = peripheral
        if let name = peripheral.name {
            print("Discovered \(name)")
            if peripheral.name == "Wavr Right" {
                if let connectedPeripheral = connectedPeripheral {
                    connectedPeripheral.delegate = self
                    centralManager.connect(connectedPeripheral)
                    centralManager.stopScan()
                }
            }
          
        }
        
    }
    
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        if central.state == .poweredOn {
            centralManager.scanForPeripherals(withServices: nil, options: nil)
        }
    }
}

extension BLEManager: CBPeripheralDelegate {
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
        guard let services = peripheral.services else {
            return
        }
        
        targetService = services.first
        if let service = services.first {
            targetService = service
            peripheral.discoverCharacteristics(nil, for: service)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        guard let characteristics = service.characteristics else {
            return
        }
        
        for characteristic in characteristics {
            if characteristic.properties.contains(.write) || characteristic.properties.contains(.writeWithoutResponse) {
                writableCharacteristic = characteristic
            }
            peripheral.setNotifyValue(true, for: characteristic)
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        guard let data = String(data: characteristic.value!, encoding: String.Encoding.utf8), let delegate = delegate else {
            return
        }
        let value = data
        delegate.commManager(bleManager: self, didReceiveString: value)
       
    }
}
