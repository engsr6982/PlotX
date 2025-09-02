declare module "minecraft" {
    export type ModalFormCancelReason = enum_class<["UserClosed", "UserBusy"]>;
    export const ModalFormCancelReason: ModalFormCancelReason; // fix ts 18042
}
