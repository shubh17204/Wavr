//
//  PianoView.swift
//  Wavr
//
//  Created by Jass Chauhan on 8/9/22.
//

import UIKit


class PianoViewController: UIViewController {
    var isConnectedToGloves: Bool = false
    
    var bleManagerLocal: BLEManager!
    
    var breakOutAngle: Int = 5
    
    var thumbAngle: Int = 0
    var indexAngle: Int = 0
    var middleAngle: Int = 0
    var ringAngle: Int = 0
    var fifthAngle: Int = 0
    
    override func viewDidLoad() {
        
        //Add piano uiViews
        
    }
    override func viewWillAppear(_ animated: Bool) {
        
    }
    override func viewDidDisappear(_ animated: Bool) {
    }
}

extension PianoViewController: BLEManagerDelegate {
    func commManager(bleManager: BLEManager, didReceiveString recvdStr: String) {
        isConnectedToGloves = true
        
        //dataLabel.text = recvdStr
        
        thumbAngle = Int(recvdStr[NSRange(location: 12, length: 2)]) ?? 0
        thumbAngle < breakOutAngle ? print("not pressed") : print("pressed")
        
        indexAngle = Int(recvdStr[NSRange(location: 15, length: 2)]) ?? 0
        indexAngle < breakOutAngle ? print("not pressed") : print("pressed")
        
        middleAngle = Int(recvdStr[NSRange(location: 18, length: 2)]) ?? 0
        middleAngle < breakOutAngle ? print("not pressed") : print("pressed")
        
        ringAngle = Int(recvdStr[NSRange(location: 21, length: 2)]) ?? 0
        ringAngle < breakOutAngle ? print("not pressed") : print("pressed")
        
        fifthAngle = Int(recvdStr[NSRange(location: 24, length: 2)]) ?? 0
        fifthAngle < breakOutAngle ? print("not pressed") : print("pressed")
    }
}

//class PianoNoteView: UIView {
//    
//    var noteName: String
//    var noteColor: UIColor
//    //audio stuff
//    
//    required init?(coder aDecoder: NSCoder) {
//        fatalError("init(coder:) has not been implemented")
//    }
//    
//    init(noteName: String, noteColor: UIColor) {
//        self.noteName = noteName
//        self.noteColor = noteColor
//        super.init(frame: .zero)
//        
//        
//    }
//    
//}
