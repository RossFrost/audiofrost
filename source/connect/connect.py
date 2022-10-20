import sys
import requests

def decode(response, output):
    RELEASE    = "release"
    ALBUM      = "title"
    TRACKLIST  = ["medium-list", "medium", "track-list", "track", "recording", "title"]
    ARTIST     = ["artist-credit", "name-credit", "artist", "name"]
    COUNTRY    = "country"
    DATE       = "date"
    DISCID     = ["medium-list", "medium", "disc-list", "disc"]
    BARCODE    = "barcode"


    from xml.dom.minidom import parseString
    
    document = parseString(response.decode("utf-8"))
    release_list = document.getElementsByTagName(RELEASE)

    with open(output, "ab") as out:
        out.truncate(0)
        out.writelines([bytes("?ENCODING: UTF-8; \n \n \n", "utf-8"), bytes('{ \n \n', "utf-8")])
        for release in release_list:
            try:
                out.writelines([
                    bytes("/START \n", "utf-8"),
                    bytes(f"    <ARIST> {release.getElementsByTagName(ARTIST[0])[0].getElementsByTagName(ARTIST[1])[0].getElementsByTagName(ARTIST[2])[0].getElementsByTagName(ARTIST[3])[0].childNodes[0].nodeValue}; \n", "utf-8"),
                    bytes(f"    <ALBUM> {release.getElementsByTagName(ALBUM)[0].childNodes[0].nodeValue}; \n", "utf-8"),

                ])

                tracks = []
                tracklist = release.getElementsByTagName(TRACKLIST[0])[0].getElementsByTagName(TRACKLIST[1])[0].getElementsByTagName(TRACKLIST[2])[0].getElementsByTagName(TRACKLIST[3])
                
                
                for track in tracklist:
                    tracks.append(bytes(f"      <TRACK{len(tracks) + 1}> {track.getElementsByTagName(TRACKLIST[4])[0].getElementsByTagName(TRACKLIST[5])[0].childNodes[0].nodeValue}; \n", "utf-8"))
                
                out.writelines([bytes("    <TRACKLIST> /OPEN \n", "utf-8")])
                out.writelines(tracks)
                out.writelines([bytes("    <TRACKLIST> /CLOSE \n", "utf-8")])
                

                out.writelines([
                    bytes(f"    <COUNTRY> {release.getElementsByTagName(COUNTRY)[0].childNodes[0].nodeValue}; \n", "utf-8"),
                    bytes(f"    <DATE> {release.getElementsByTagName(DATE)[0].childNodes[0].nodeValue}; \n", "utf-8"),
                    bytes(f"    <DISCID> {release.getElementsByTagName(DISCID[0])[0].getElementsByTagName(DISCID[1])[0].getElementsByTagName(DISCID[2])[0].getElementsByTagName(DISCID[3])[0].getAttribute('id')}; \n", "utf-8"),
                    bytes(f"    <BARCODE> {release.getElementsByTagName(BARCODE)[0].childNodes[0].nodeValue}; \n", "utf-8"),
                    bytes("/END \n\n","utf-8")
                ])
            except:
               continue
        out.writelines([bytes('} \n', "utf-8")])


        out.close()


def main():
    args = sys.argv[1:]

    response = requests.get(args[0]).content
    output = f"{args[1]}.frost"
    decode(response, output)

if __name__ == "__main__":
    main()