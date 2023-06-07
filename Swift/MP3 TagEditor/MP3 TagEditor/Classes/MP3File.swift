//
//  MP3File.swift
//  MP3 TagEditor
//
//  Created by Paul Rübenich on 06.06.23.
//

import Foundation
import AVFoundation

class MP3File: Identifiable {
    
    let id: UUID
    var file_url: URL?
    var file_name: String
    var song_name: String
    var artist: String
    var album: String
    var year: String
    var genre: String
    
    
    init(file_url: URL?, file_name: String, song_name: String, artist: String, album: String, year: String, genre: String){
        self.id = UUID()
        self.file_url = file_url
        self.file_name = file_name
        self.song_name = song_name
        self.artist = artist
        self.album = album
        self.year = year
        self.genre = genre
    }
    
    init(){
        self.id = UUID()
        self.file_url = nil
        self.file_name = ""
        self.song_name = ""
        self.artist = ""
        self.album = ""
        self.year = ""
        self.genre = ""
    }
    
    public func printID() {
        print(self.id)
    }
    
    public func set_file_url(file_url: URL) {
        self.file_url = file_url
    }
    
    public func set_file_name(file_name: String) {
        self.file_name = file_name
    }
    
    public func set_song_name(song_name: String) {
        self.song_name = song_name
    }
    
    public func set_artist(artist: String) {
        self.artist = artist
    }
    
    public func set_album(album: String) {
        self.album = album
    }
    
    public func set_year(year: String) {
        self.year = year
    }
    
    public func set_genre(genre: String) {
        self.genre = genre
    }
    
    
    public func get_file_name() -> String {
        return self.file_name
    }
    
    public func get_song_name() -> String {
        return self.song_name
    }
    
    public func get_artist() -> String {
        return self.artist
    }
    
    public func get_album() -> String {
        return self.album
    }
    
    public func get_year() -> String {
        return self.year
    }
    
    public func get_genre() -> String {
        return self.genre
    }
    
    
    func open_MP3_file(url: URL?) async -> Void {
        if(url != nil) {
            let asset = AVAsset(url: url!)
            do {
                let metadata = try await asset.load(.metadata)
                self.set_file_url(file_url: url!)
                self.set_file_name(file_name: url!.lastPathComponent)
                print(metadata)
                for item in metadata {
                    do {
                        if let key = item.commonKey?.rawValue,
                           let value = try await item.load(.value) {
                            switch key {
                            case "title":
                                if let songName = value as? String {
                                    self.set_song_name(song_name: songName)
                                }
                            case "artist":
                                if let artist = value as? String {
                                    self.set_artist(artist: artist)
                                }
                            case "albumName":
                                if let albumName = value as? String {
                                    self.set_album(album: albumName)
                                }
                            case "year":
                                if let year = value as? String {
                                    self.set_year(year: year)
                                }
                            case "type":
                                if let genre = value as? String {
                                    self.set_genre(genre: genre)
                                }
                            default:
                                continue
                            }
                        }
                        
                    }
                    catch {
                        print("Error: \(error)")
                    }
                }
                
            } catch {
                print("Error: \(error)")
            }
        }
        else {
            print("Es wurde keine Datei ausgewählt!")
        }
    }
    
    
    
    func write_MP3_file() async -> Void {
        do {
            let asset = AVAsset(url: self.file_url!)
            let metadata = try await asset.load(.metadata)
            let metadataList = metadata.compactMap { item -> AVMutableMetadataItem? in
                guard let mutableItem = item.copy() as? AVMutableMetadataItem else {
                    return nil
                }
                return mutableItem
            }
            
            for item in metadataList {
                if let key = item.commonKey?.rawValue {
                    switch key {
                    case "title":
                        item.value = "Neuer Songname" as NSString
                    case "artist":
                        item.value = "Neuer Interpret" as NSString
                    case "albumName":
                        item.value = "Neues Album" as NSString
                    case "genre":
                        item.value = "Neues Genre" as NSString
                    case "year":
                        item.value = "Neues Jahr" as NSString
                    default:
                        continue
                    }
                }
            }
            
            let exportSession = AVAssetExportSession(asset: asset, presetName: AVAssetExportPresetPassthrough)
            let outputFileURL = URL(fileURLWithPath: self.file_url!.path)
            exportSession?.outputURL = outputFileURL
            exportSession?.outputFileType = .mp3
            exportSession?.metadata = metadataList as [AVMetadataItem]
            exportSession?.exportAsynchronously {
                if exportSession?.status == .completed {
                    print("Metadaten erfolgreich geändert.")
                } else if exportSession?.status == .failed {
                    print("Fehler beim Ändern der Metadaten.")
                }
            }
        }
        catch {
            print("Error: \(error)")
        }
    }
   
}
