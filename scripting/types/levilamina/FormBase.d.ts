declare module "levilamina" {
    export enum ModalFormCancelReason {
        UserClosed = 0,
        UserBusy = 1,
    }
    export type FormCancelReason = optional<ModalFormCancelReason>;
}
