from volgactf.final.service_api import ServiceAPIHelper
from volgactf.final.capsule_api import CapsuleAPIHelper
from volgactf.final.flag_api import FlagAPIHelper
import jwt

#h = CapsuleAPIHelper('https://final.volgactf.ru')
PUBLIC_KEY = '''-----BEGIN PUBLIC KEY-----
MFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEtZyXnUYUbDFfOhIJsolWMQPvLcFZ
d6R0WuZXhOpS55O+iezup/8Ky+J5w7EWPpVYzvGJzjaknodj2dU+AS/VKA==
-----END PUBLIC KEY-----'''
import requests

from server import app
from server.models import FlagStatus, SubmitResult

class FlagStatus(Enum):
    QUEUED = 0
    SKIPPED = 1
    ACCEPTED = 2
    REJECTED = 3


Flag = namedtuple('Flag', ['flag', 'sploit', 'team', 'time', 'status', 'checksystem_response'])
SubmitResult = namedtuple('SubmitResult', ['flag', 'status', 'checksystem_response'])

RESPONSES = {
    FlagStatus.QUEUED: ['ERROR_RATELIMIT' ],
    FlagStatus.ACCEPTED: ['SUCCESS'],
    FlagStatus.REJECTED: ['ERROR_FLAG_INVALID','ERROR_ACCESS_DENIED', 'ERROR_COMPETITION_NOT_STARTED', 'ERROR_COMPETITION_PAUSED', 'ERROR_COMPETITION_FINISHED', 'ERROR_FLAG_EXPIRED', 'ERROR_FLAG_YOUR_OWN', 'ERROR_FLAG_SUBMITTED', 'ERROR_FLAG_NOT_FOUND','ERROR_SERVICE_STATE_INVALID'],
}

TIMEOUT = 5

def decodeFlags(flags):
    decodedFlags = []
    for flag in flags:
        try:
            decoded = jwt.decode(flag, PUBLIC_KEY, algorithms=["ES256"])
            decodedFlags.append(decoded['flag'])
        except:
            print(flag)
            pass
    return decodedFlags
        
def remoteDecodeFlags(flags,config):
    decodedFlags = []
    decodeHelper = CapsuleAPIHelper(config["SYSTEM_URL"])
    for flag in flags:
        response = decodeHelper.decode(flag)
        if response['code'].name == 'SUCCESS':
            decodedFlags.append(flag)
    return decodedFlags
    
    
def submit_flag(flags, config, PUBLIC_KEY=PUBLIC_KEY):
    decodedFlags = []
    if PUBLIC_KEY:
        decodedFlags = decodeFlags(flags)
    if len(decodedFlags) == 0:
        decodedFlags = remoteDecodeFlags(flags,config)
    else:
        return
    h = FlagAPIHelper(config["SYSTEM_URL"])
    answers = h.submit(*flags)
    for answer in answers:
        code = answer['code'].name
        for status, possible_codes in RESPONSES.items():
            if code in possible_codes:
                found_status = status
                break
            else:
                found_status = FlagStatus.QUEUED
        yield SubmitResult(answer.flag, found_status, code.name)
