//
//  BLE Services.swift
//  Wavr
//
//  Created by Jass Chauhan on 8/7/22.
//

import Foundation

enum Services: String, Codable, CaseIterable {
    case ping = "10"
    case setMainBLEToken = "11"
    case removeMainBLEToken = "12"
    case restart = "19"
    
    case stopHaptics = "20"
    case startHaptics = "21"
    case hapChimeStart = "22"
    case hapChimeStop = "23"
    case hapChimeSuccess = "24"
    case hapChimeError = "25"
    
    case stopLED = "30"
    case setRedLED = "31"
    case setGreenLED = "32"
    case setBlueLED = "33"
    case setCyanLED = "34"
    case setPurpleLED = "35"
    case setYellowLED = "36"
    case setWhiteLED = "37"
    
    case forceCalib = "40"
    case condCalib = "41"
    
    case ReqCharac = "50"
    case ReqMain = "51"
    case ReqFlex = "52"
    case ReqIMU = "53"
    case ReqPushButt = "54"
    case ReqBatt = "55"
    case ReqParityTok = "56"
    case ReqLEDHapState = "57"
    
    case EraseFlash = "70"
    case DumpFlash = "71"
    
    case test = "404"
}
